/*
* "Melody" library
* Created by: Matan Bright
*
*/

#include "Melody.h"																							// Include the main header file of the "Melody" library
#include "ArrayList.cpp"																					// Include the main code file of the "ArrayList" library
#include "Queue.cpp"																						// Include the main code file of the "Queue" library


static volatile Melody *melodyInstances[TONE_GENERATION_TIMERS_COUNT];										// Set a static array of the class instances (because each instance is assigned to a free timer, we have limited instances count)
static volatile Note currentNote[TONE_GENERATION_TIMERS_COUNT];												// Set a static array of the current note of each melody object
static volatile float currentMillis[TONE_GENERATION_TIMERS_COUNT];											// Set a static array of the current milliseconds which passed from the last note for each melody object


// This is the constructor of the class. It is called when you build an object from the class
Melody::Melody(int tempo = DEFAULT_MELODY_TEMPO, int snap = DEFAULT_MELODY_SNAP) {
	int instancesCount = 0;																						// Set a variable for counting the current instances count
	for (int i = 0; i < TONE_GENERATION_TIMERS_COUNT; i++)														// Loop until we reach the count of the tone generation timers
		if (melodyInstances[i] != 0)																				// If the melody instance with index 'i' is not null
			instancesCount++;																							// Increment the current instances count by 1
	if (instancesCount == 0)																					// If this is the first instance
		ENABLE_NOTES_TIMING_TIMER_INTERRUPTS();																		// Enable the notes timing timer (because this timer is shared by all the instances, so if we have at least 1 instance, we will need to enable it)

	this->melodyInstanceIndex = -1;																				// Set the melody instance index of the current object to a default value of -1
	this->valid = false;																						// Set the validation status of the current object to a default value of 'false'
	bool reachedMaxInstances = true;																			// Set a variable for determining if we reached the maximum instances count (and set to a default value of 'true')
	int freeInstanceIndex = -1;																					// Set a variable for determining the index of the first free instance, if there one (and set to a default value of -1)
	for (int i = 0; i < TONE_GENERATION_TIMERS_COUNT; i++) {													// Loop until we reach the count of the tone generation timers
		if (melodyInstances[i] == 0) {																				// If the melody instance with index 'i' is null
			reachedMaxInstances = false;																				// Set that variable value to 'false', for indicating we still have free instances
			freeInstanceIndex = i;																						// Set that variable value to 'i', for indicating the index of the first free instance
			break;																										// Quit the loop immediately (because we have a free instance)
		}
	}
	if (!reachedMaxInstances) {																					// If we have free instances
		this->melodyInstanceIndex = freeInstanceIndex;																// Set the melody instance index of the current object to the index of the first free instance
		this->valid = true;																							// Set the validation status of the current object to 'true', for indicating that the object is valid
		melodyInstances[this->melodyInstanceIndex] = this;															// Add the current new object to the static array of the class instances
		this->pin = -1;																								// Set the attached pin number of the current object to a default value of -1 (no pin)
		if (tempo < 1)																								// If the selected tempo (beats-per-minute) value is below 1
			tempo = 1;																									// Set the selected tempo (beats-per-minute) value of the current object to 1 (because the value must be equal to or above 1)
		if (snap < 1)																								// If the selected snap (bars-per-beat) value is below 1
			snap = 1;																									// Set the selected snap (bars-per-beat) value of the current object to 1 (because the value must be equal to or above 1)
		this->tempo = tempo;																						// Set the tempo (beats-per-minute) value of the current object to the selected value
		this->snap = snap;																							// Set the snap (bars-per-beat) value of the current object to the selected value
		this->melodyNotes = new ArrayList<Note>();																	// Initialize the notes array-list of the current object
		this->currentNoteIndex = -1;																				// Set the current playing note's index of the current object to a default value of -1 (no notes are playing)
		this->attachedToPin = false;																				// Set the pin attachement status variable value to 'false', for indicating that the current object is not attached to a pin
		this->state = STOPPED;																						// Set the state variable value to 'STOPPED', for indicating that the current object's melody is stopped
		this->playInLoop = false;																					// Set the loop play status variable value to 'false', for indicating that the current object's melody will not play in loop
		this->muted = false;																						// Set the mute status variable value to 'false', for indicating that the current object's melody is not muted
	}
}

// This is the copy constructor of the class. It is called on the copied object when an object is assigned to the copied object. For the "Melody" class, copying is not allowed, because each object is statically assigned to a free timer
Melody::Melody(const Melody &copy) {
	this->valid = false;																						// Set the validation status of the current object to 'false', for indicating that the copied object is invalid and useless
}

// This is a function that returns the validation status of the object
bool Melody::isValid() {
	return this->valid;																							// Return the validation status of the current object
}

// This is a function that returns the pin attachement status of the object
bool Melody::isAttached() {
	return this->attachedToPin;																					// Return the pin attachement status of the current object
}

// This is a function that returns the tempo (beats-per-minute) value of the object
int Melody::getTempo() {
	return this->tempo;																							// Return the tempo (beats-per-minute) value of the current object
}

// This is a function that sets the tempo (beats-per-minute) value of the object to a new value
void Melody::setTempo(int tempo) {
	if (tempo < 1)																								// If the selected tempo (beats-per-minute) value is below 1
		tempo = 1;																									// Set the selected tempo (beats-per-minute) value of the current object to 1 (because the value must be equal to or above 1)
	float tempoRatio = (float)tempo / (float)this->tempo;														// Set a variable for the ratio of the change in the tempo (beats-per-minute), and calculate it by dividing the new value by the old value
	this->tempo = tempo;																						// Set the tempo (beats-per-minute) value of the current object to the selected value
	for (int i = 0; i < this->melodyNotes->getLength(); i++) {													// Loop until we reach the count of the melody notes of the current object's melody
		Note note = this->melodyNotes->getAt(i);																	// Set a temporary variable for holding the note with the index 'i' of the melody
		this->melodyNotes->replaceAt(i, { note.frequency, note.duration / tempoRatio });							// Replace the old note with the index 'i' with a new note that has the same frequency, but the duration is divided by the ratio of the change in the tempo (beats-per-minute)
		if (i == this->currentNoteIndex)																			// If 'i' equals to the index of the current playing note of the current object
			currentNote[this->melodyInstanceIndex].duration = note.duration / tempoRatio;								// Update the duration of the current playing note of the current object to the new duration
	}
}

// This is a function that returns the snap (bars-per-beat) value of the object
int Melody::getSnap() {
	return this->snap;																							// Return the snap (bars-per-beat) value of the current object
}

// This is a function that sets the snap (bars-per-beat) value of the object to a new value
void Melody::setSnap(int snap) {
	if (snap < 1)																								// If the selected snap (bars-per-beat) value is below 1
		snap = 1;																									// Set the selected snap (bars-per-beat) value of the current object to 1 (because the value must be equal to or above 1)
	float snapRatio = (float)snap / (float)this->snap;															// Set a variable for the ratio of the change in the snap (bars-per-beat), and calculate it by dividing the new value by the old value
	this->snap = snap;																							// Set the snap (bars-per-beat) value of the current object to the selected value
	for (int i = 0; i < this->melodyNotes->getLength(); i++) {													// Loop until we reach the count of the melody notes of the current object's melody
		Note note = this->melodyNotes->getAt(i);																	// Set a temporary variable for holding the note with the index 'i' of the melody
		this->melodyNotes->replaceAt(i, { note.frequency, note.duration / snapRatio });								// Replace the old note with the index 'i' with a new note that has the same frequency, but the duration is divided by the ratio of the change in the snap (bars-per-beat)
		if (i == this->currentNoteIndex)																			// If 'i' equals to the index of the current playing note of the current object
			currentNote[this->melodyInstanceIndex].duration = note.duration / snapRatio;								// Update the duration of the current playing note of the current object to the new duration
	}
}

// This is a function that returns the state of the object's melody ('PLAYING', 'PAUSED' or 'STOPPED')
MelodyState Melody::getState() {
	return this->state;																							// Return the state of the object's melody
}

// This is a function that returns the mute status of the object's melody
bool Melody::isMuted() {
	return this->muted;																							// Return the mute status of the object's melody
}

// This is a function that attaches the object to a pin on the micro-controller
void Melody::attach(int pin) {
	if (this->valid) {																							// If the current object is valid
		if (!this->attachedToPin) {																					// If the current object is not attached to a pin
			if (pin >= 0) {																								// If the selected pin number is equal to or above 0 (because there are no negative pin numbers)
				this->pin = pin;																							// Set the attached pin number of the current object to the selected pin number
				pinMode(this->pin, OUTPUT);																					// Set the pin mode of the current object's attached pin on the micro-controller to 'OUTPUT'
				digitalWrite(this->pin, LOW);																				// Set the pin state of the current object's attached pin on the micro-controller to 'LOW'
				this->attachedToPin = true;																					// Set the pin attachement status variable value to 'true', for indicating that the current object is attached to a pin
			}
		}
	}
}

// This is a function that detaches the object from a pin on the micro-controller
void Melody::detach() {
	if (this->valid) {																							// If the current object is valid
		this->stop();																								// Call the "stop" function of the current object
		this->attachedToPin = false;																				// Set the pin attachement status variable value to 'false', for indicating that the current object is not attached to a pin
		pinMode(this->pin, INPUT);																					// Set the pin mode of the current object's attached pin on the micro-controller to 'INPUT' (this is the default value of the pins)
		this->pin = -1;																								// Set the attached pin number of the current object to a default value of -1 (no pin)
	}
}

// This is a function that adds a note to the object's notes queue
void Melody::addNote(int frequency, int noteBars) {
	if (this->valid) {																							// If the current object is valid
		if (this->attachedToPin) {																					// If the current object is attached to a pin
			if (noteBars > 0) {																							// If the selected note bars number is above 0
				if (frequency < 0)																							// If the selected frequency value is below 0
					frequency = 0;																								// Set the selected frequency value of the current object to 0 (because the value must be equal to or above 0)
				float duration = 1.0 / (this->tempo / 60.0) * 1000.0 / this->snap * noteBars;								// Set a variable for the duration (in milliseconds) of the note, and calculate it from the current object's tempo (beats-per-second), the current object's snap (bars-per-beat) and the selected note bars count
				this->melodyNotes->add({ frequency, duration });															// Insert a new note to the current object's melody notes array-list with the selected frequency and the calculated duration
			}
		}
	}
}

// This is a function that stops the object's melody playing and deletes all the object's melody notes
void Melody::clear() {
	if (this->valid) {																							// If the current object is valid
		this->stop();																								// Call the "stop" function of the current object
		delete this->melodyNotes;																					// Delete the notes array-list of the current object from the heap memory
		this->melodyNotes = new ArrayList<Note>();																	// Initializing a new notes array-list for the current object
	}
}

// This is a function that causes the object to play the melody from the notes queue (with an option for looping), or resume the melody playing if it was paused
void Melody::play(bool playInLoop = false) {
	if (this->valid) {																							// If the current object is valid
		if (this->state == STOPPED)																					// If the object's melody is stopped (because we want to change the loop playing state only when the melody is completely stopped)
			this->playInLoop = playInLoop;																				// Set the loop play status variable value to the selected value
		else if (this->state == PAUSED)																				// If the object's melody is paused (because we want to immediately start the melody from the last uncompleted bar instead of waiting for the next)
			if (!this->muted)																							// If the object's melody is not muted
				ENABLE_TONE_GENERATION_TIMER(this->melodyInstanceIndex);													// Enable the tone generation timer of the current object. It causes the buzzer to start making sounds
		this->state = PLAYING;																						// Set the state variable value to 'PLAYING', for indicating that the current object's melody is playing
	}
}

// This is a function that causes the object to pause the melody playing. Calling the "play" function will resume the melody playing
void Melody::pause() {
	if (this->valid) {																							// If the current object is valid
		this->state = PAUSED;																						// Set the state variable value to 'PAUSED', for indicating that the current object's melody is paused
		DISABLE_TONE_GENERATION_TIMER(this->melodyInstanceIndex);													// Disable the tone generation timer of the current object. It causes the buzzer to stop making sounds
		digitalWrite(this->pin, LOW);																				// Set the pin state of the current object's attached pin on the micro-controller to 'LOW'
	}
}

// This is a function that causes the object to stop the melody playing. Calling the "play" function will not resume the melody playing
void Melody::stop() {
	if (this->valid) {																							// If the current object is valid
		this->state = STOPPED;																						// Set the state variable value to 'STOPPED', for indicating that the current object's melody is stopped
		this->playInLoop = false;																					// Set the loop play status variable value to 'false', for indicating that the current object's melody will not play in loop
		DISABLE_TONE_GENERATION_TIMER(this->melodyInstanceIndex);													// Disable the tone generation timer of the current object. It causes the buzzer to stop making sounds
		digitalWrite(this->pin, LOW);																				// Set the pin state of the current object's attached pin on the micro-controller to 'LOW'
		this->currentNoteIndex = -1;																				// Set the current playing note's index of the current object to a default value of -1 (no notes are playing)
	}
}

// This is a function that causes the object to mute the melody playing. The melody will still be playing, but you will not hear it
void Melody::mute() {
	if (this->valid) {																							// If the current object is valid
		this->muted = true;																							// Set the mute status variable value to 'true', for indicating that the current object's melody is muted
		DISABLE_TONE_GENERATION_TIMER(this->melodyInstanceIndex);													// Disable the tone generation timer of the current object. It causes the buzzer to stop making sounds
		digitalWrite(this->pin, LOW);																				// Set the pin state of the current object's attached pin on the micro-controller to 'LOW'
	}
}

// This is a function that causes the object to unmute the melody playing. If the melody is playing, you will be able to hear it
void Melody::unmute() {
	if (this->valid) {																							// If the current object is valid
		this->muted = false;																						// Set the mute status variable value to 'false', for indicating that the current object's melody is not muted
		if (this->state == PLAYING)																					// If the object's melody is playing (because we want to immediately start the melody from the current uncompleted bar instead of waiting for the next)
			ENABLE_TONE_GENERATION_TIMER(this->melodyInstanceIndex);													// Enable the tone generation timer of the current object. It causes the buzzer to start making sounds
	}
}

// This is the destructor of the class. It is called when an object of the class is destroied (by losing scope for a value-type object, or calling "delete" on a reference-type object). It is intended for freeing the instance and the timer from the destrioed object
Melody::~Melody() {
	int instancesCount = 0;																						// Set a variable for counting the current instances count
	for (int i = 0; i < TONE_GENERATION_TIMERS_COUNT; i++)														// Loop until we reach the count of the tone generation timers
		if (melodyInstances[i] != 0)																				// If the melody instance
			instancesCount++;																							// Increment the current instances count by 1
	if (instancesCount == 1)																					// If this is the last instance
		DISABLE_NOTES_TIMING_TIMER_INTERRUPTS();																	// Disable the notes timing timer (because we have now 0 instances, so there is no need for the timer)

	this->detach();																								// Call the "detach" function of the current object
	melodyInstances[this->melodyInstanceIndex] = 0;																// Remove the current object from the static array of the class instances
	delete this->melodyNotes;																					// Delete the notes array-list of the current object from the heap memory
}



// This is the interrupt service routine of the notes timing timer. It is called on each tick of timer0 (it ticks by default at ~1000Hz [~1ms each tick] on 16MHz clock speed. Lower/higher clock speed will cause the frequency to be lower/higher proportionaly)
ISR(NOTES_TIMING_TIMER_INTERRUPT_SERVICE_ROUTINE) {
	for (int i = 0; i < TONE_GENERATION_TIMERS_COUNT; i++) {													// Loop until we reach the count of the tone generation timers
		if (melodyInstances[i] != 0) {																				// If the melody instance with index 'i' is not null
			if (melodyInstances[i]->state == PLAYING)																	// If the melody instance with index 'i' is playing melody
				currentMillis[i] += 16000000.0 / SYSTEM_CLOCK_FREQUENCY;													// Add the passed time (in milliseconds) from the last timer tick (for example: on 8MHz clock speed, the timer will run at ~500Hz [~2ms each tick])
			else if (melodyInstances[i]->state == STOPPED) {															// If the melody instance with index 'i' stopped playing melody
				currentMillis[i] = 0;																						// Set the current milliseconds value of the melody instance with index 'i' to 0
				currentNote[i] = { 0, 0 };																					// Initialize the current note of the melody instance with index 'i' 
			}
		}
	}

	for (int i = 0; i < TONE_GENERATION_TIMERS_COUNT; i++) {													// Loop until we reach the count of the tone generation timers
		if (melodyInstances[i] != 0) {																				// If the melody instance with index 'i' is not null
			if (melodyInstances[i]->attachedToPin) {																	// If the melody instance with index 'i' is attached to pin
				if (melodyInstances[i]->state == PLAYING) {																	// If the melody instance with index 'i' is playing melody
					if (currentMillis[i] >= currentNote[i].duration) {															// If the current milliseconds of the melody instance with index 'i' is equal to or larger than the duration of its current note
						currentMillis[i] = 0;																						// Set the current milliseconds value of the melody instance with index 'i' to 0
						melodyInstances[i]->currentNoteIndex++;																		// Increment the current playing note's index of the melody instance with index 'i' by 1
						if (melodyInstances[i]->currentNoteIndex >= melodyInstances[i]->melodyNotes->getLength()) {					// If the current playing note's index of the melody instance with index 'i' is equal or above the count of the melody notes
							if (melodyInstances[i]->playInLoop)																			// If the melody instance with index 'i' is playing its melody in loop
								melodyInstances[i]->currentNoteIndex = 0;																	// Set the current playing note's index of the melody instance with index 'i' to 0 (for looping)
							else {																										// If the melody instance with index 'i' is not playing its melody in loop
								melodyInstances[i]->stop();																					// Call the "stop" function of the melody instance with index 'i'
								continue;																									// Skip to the next iteration of the loop (because the melody instance with index 'i' has reached the end of its melody)
							}
						}
						currentNote[i] = melodyInstances[i]->melodyNotes->getAt(melodyInstances[i]->currentNoteIndex);				// Assign the current note of the melody instance with index 'i' to the current note variable
						INITIALIZE_TONE_GENERATION_TIMER(i, currentNote[i].frequency);												// Initialize the tone generation timer of the instance with index 'i' with the current note's frequency
						digitalWrite(melodyInstances[i]->pin, LOW);																	// Set the pin state of the attached pin of the melody instance with index 'i' on the micro-controller to 'LOW'
						if (!melodyInstances[i]->muted)																				// If the melody playing of the melody instance with index 'i' is not muted and the current note frequency is above 0Hz
							ENABLE_TONE_GENERATION_TIMER(i);																			// Enable the tone generation timer of the instance with index 'i'. It causes the buzzer to start making sounds
					}
				}
			}
		}
	}
}

#if TONE_GENERATION_TIMERS_COUNT >= 1																		// If there is at least 1 tone generation timer
// This is the interrupt service routine of a tone generation timer (timer1)
ISR(TIMER1_TONE_GENERATION_TIMER_INTERRUPT_SERVICE_ROUTINE) {
	digitalWrite(melodyInstances[0]->pin, !digitalRead(melodyInstances[0]->pin));								// Toggle the pin state of the attached pin of the melody instance with index 0 on the micro-controller
}
#endif

#if TONE_GENERATION_TIMERS_COUNT >= 2																		// If there are at least 2 tone generation timers
// This is the interrupt service routine of a tone generation timer (timer3)
ISR(TIMER3_TONE_GENERATION_TIMER_INTERRUPT_SERVICE_ROUTINE) {
	digitalWrite(melodyInstances[1]->pin, !digitalRead(melodyInstances[1]->pin));								// Toggle the pin state of the attached pin of the melody instance with index 1 on the micro-controller
}
#endif

#if TONE_GENERATION_TIMERS_COUNT >= 3																		// If there are at least 3 tone generation timers
// This is the interrupt service routine of a tone generation timer (timer4)
ISR(TIMER4_TONE_GENERATION_TIMER_INTERRUPT_SERVICE_ROUTINE) {
	digitalWrite(melodyInstances[2]->pin, !digitalRead(melodyInstances[2]->pin));								// Toggle the pin state of the attached pin of the melody instance with index 2 on the micro-controller
}
#endif

#if TONE_GENERATION_TIMERS_COUNT >= 4																		// If there are at least 4 tone generation timers
// This is the interrupt service routine of a tone generation timer (timer5)
ISR(TIMER5_TONE_GENERATION_TIMER_INTERRUPT_SERVICE_ROUTINE) {
	digitalWrite(melodyInstances[3]->pin, !digitalRead(melodyInstances[3]->pin));								// Toggle the pin state of the attached pin of the melody instance with index 3 on the micro-controller
}
#endif
