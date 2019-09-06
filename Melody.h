/*
* "Melody" library
* Created by: Matan Bright
*
*/


#if !defined(MELODY)																						// If 'MELODY' is not defined. It means that this file is included at the first time
#define MELODY																								// Define 'MELODY' for preventing multiple inclusions of this file

#include "Melody_definitions.h"																				// Include the definitions header file of the "Melody" library
#include "Queue.h"																							// Include the main header file of the "Queue" library
#include "ArrayList.h"																						// Include the main header file of the "ArrayList" library
#include "PianoNotes.h"																						// Include the main header file of the "PianoNotes" library


enum MelodyState {																							// Declare an enum for determining the state of the melody playing
	PLAYING,																									// 'PLAYING': means that the melody is playing
	PAUSED,																										// 'PAUSED': means that the melody is paused
	STOPPED																										// 'STOPPED': means that the melody is stopped
};

struct Note {																								// Declare a struct for representing a note of the melody
public:
	volatile int frequency;																						// Variable that represents the note's frequency (in Hz)
	volatile float duration;																					// Variable that represents the note's duration (in milliseconds)
};

class Melody {																								// Declare a class for representing an object which helps to make a melody with a buzzer
public:
	volatile int melodyInstanceIndex;																			// Variable that represents the instance index of the object
	volatile bool valid;																						// Variable that determine if the object is valid or not
	volatile int pin;																							// Variable that represents the number of the object's attached pin
	volatile int tempo;																							// Variable that represents the object's melody's tempo (beats-per-minute)
	volatile int snap;																							// Variable that represents the object's melody's snap (bars-per-beat)
	volatile ArrayList<Note> *melodyNotes;																		// Array-list that stores the notes of the melody
	volatile int currentNoteIndex;																				// Variable that represents the current playing note's index of the object
	volatile bool attachedToPin;																				// Variable that determine if the object is attached to a pin on the micro-controller or not
	volatile MelodyState state;																					// Variable that represents the current state of the object's melody playing (according to the "MelodyState" enum)
	volatile bool playInLoop;																					// Variable that determine if the object's melody will play in loop or not
	volatile bool muted;																						// Variable that determine if the object's melody is muted or not
	Melody(int tempo = DEFAULT_MELODY_TEMPO, int snap = DEFAULT_MELODY_SNAP);									// The constructor of the class
	Melody(const Melody &copy);																					// The copy constructor of the class
	bool isValid();																								// Function that returns the validation status of the object
	bool isAttached();																							// Function that returns the pin attachement status of the object
	int getTempo();																								// Function that returns the tempo (beats-per-minute) value of the object
	void setTempo(int tempo);																					// Function that sets the tempo (beats-per-minute) value of the object to a new value
	int getSnap();																								// Function that returns the snap (bars-per-beat) value of the object
	void setSnap(int snap);																						// Function that sets the snap (bars-per-beat) value of the object to a new value
	MelodyState getState();																						// Function that returns the state of the object's melody ('PLAYING', 'PAUSED' or 'STOPPED')
	bool isMuted();																								// Function that returns the mute status of the object's melody
	void attach(int pin);																						// Function that attaches the object to a pin on the micro-controller
	void detach();																								// Function that detaches the object from a pin on the micro-controller
	void addNote(int frequency, int noteBars);																	// Function that adds a note to the object's notes queue
	void clear();																								// Function that stops the object's melody playing and deletes all the object's melody notes
	void play(bool playInLoop = false);																			// Function that causes the object to play the melody from the notes queue (with an option for looping), or resume the melody playing if it was paused
	void pause();																								// Function that causes the object to pause the melody playing
	void stop();																								// Function that causes the object to stop the melody playing
	void mute();																								// Function that causes the object to mute the melody playing
	void unmute();																								// Function that causes the object to unmute the melody playing
	~Melody();																									// The destructor of the class
};

#endif
