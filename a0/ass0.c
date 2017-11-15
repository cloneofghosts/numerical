/***************************************************************************************************
Filename:			ass0.c
Version:			1.0
Purpose:			To allow the user to add Frames to the Animation, delete Frames from the Animation,
				and run the Animation. Once run it displays each Frame in the animation every second
				with the name of the frame and the time of the Animation being displayed.
**************************************************************************************************/
#define _CRT_SECURE_NO_WARNINGS

#define _CRTDBG_MAP_ALLOC	// need this to get the line identification
//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF); // in main, after local declarations
//NB must be in debug build

#include <crtdbg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef enum { FALSE = 0, TRUE } BOOL;

struct Frame {
	char* fileName;
	struct Frame* pNext;
};

struct Animation {
	struct Frame* frames;
};

// Forward declarations
void initAnimation(struct Animation*);
void insertFrame(struct Animation*);
void deleteFrames(struct Animation*);
void runFrames(struct Animation*);

/***************************************************************************************************
Function name:		main
Purpose:		main function
			Main menu for the Animation to allow the user to add/remove Frames from the animation
			and run the Animation.
In parameters:		none
Out parameters:		0 for sucessful execution
Version:		1.0
***************************************************************************************************/
int main(void)
{
	char response;
	BOOL RUNNING = TRUE;
	struct Animation A;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	initAnimation(&A);

	while (RUNNING)
	{
		printf("MENU\n 1. Insert a Frame\n 2. Delete all the Frames\n 3. Run the Animation\n 4. Quit\n");
		scanf("%c", &response);
		switch (response)
		{
		case '1':insertFrame(&A); break;
		case '2':deleteFrames(&A); break;
		case '3':runFrames(&A); break;
		case '4':RUNNING = FALSE; deleteFrames(&A); break;
		default:printf("Please enter a valid option\n");
		}
		printf("\n");
		while ((response = getchar()) != '\n' && response != EOF);// clear input buffer
	}
	return 0;
}

/***************************************************************************************************
Function name:		initAnimation
Purpose:		Initilizes the frames in the Animation structure to NULL
In parameters:		animation structure
Out parameters:		none
Version:		1.0
***************************************************************************************************/
void initAnimation(struct Animation* pA)
{
	pA->frames = NULL;
}

/***************************************************************************************************
Function name:		insertFrame
Purpose:		Allows the user to add a new Frame to the Animation
In parameters:		animation structure
Out parameters:		none
Version:		1.0
***************************************************************************************************/
void insertFrame(struct Animation* pA) 
{
	struct Frame *newFrame = malloc(sizeof(struct Frame));
	struct Frame *iterator = pA->frames;
	int count = 0, pos, len;
	char str[255];

	newFrame->pNext = NULL;
	
	printf("Insert a Frame into the Animation\nPlease enter the Frame filename: ");
	scanf("%254s", str);

	//gets the length of the input string and makes memory for it in the new Frame
	len = strlen(str);
	newFrame->fileName = (char*)malloc(len * sizeof(char*));
	//copies the name from str to the new Frame
	strcpy(newFrame->fileName, str);

	//if there are no frames in the animation make the new one the first frame
	if (pA->frames == NULL) {
		printf("This is the first frame in the animation\n");
		pA->frames = newFrame;
	}
	else {
		//gets the count of how many frames are in the animation
		while (iterator) {
			count++;
			iterator = iterator->pNext;
		}
		printf("There are %d frame(s) in the list. Please specify the position (<=%d) to insert at: ", count, count);
		scanf("%d", &pos);
		
		//checks if the position is bigger than the amount of frames, if so add it to the end
		if (pos > count)
			pos = count;

		count = 0;
		iterator = pA->frames;

		//loops to find the correct position to place the new frame
		while (iterator && count < pos-1) {
			count++;
			iterator = iterator->pNext;
		}
		//if the frame is the first one to be added in the animation
		if (count == 0 && pos == 0) {
			newFrame->pNext = pA->frames;
			pA->frames = newFrame;
		}
		else {
			newFrame->pNext = iterator->pNext;
			iterator->pNext = newFrame;
		}
	}

}
/***************************************************************************************************
Function name:		deleteFrames
Purpose:		Loops through and frees the all the memory associated with the Animation Frames
In parameters:		animation structure
Out parameters:		none
Version:		1.0
***************************************************************************************************/
void deleteFrames(struct Animation* pA)
{
	struct Frame* tempFrame;

	//null check
	if (pA->frames == NULL)
		return;

	printf("Delete all Frames in the animation\n");

	//loop through and free each frame in the animation
	while (pA->frames) {
		tempFrame = pA->frames;
		free(tempFrame->fileName);
		pA->frames = pA->frames->pNext;
		free(tempFrame);
	}
}
/***************************************************************************************************
Function name:		runFrames
Purpose:		Prints out each every frame in the animation
In parameters:		animation structure
Out parameters:		none
Version:		1.0
***************************************************************************************************/
void runFrames(struct Animation* pA)
{
	int counter = 0;
	time_t startsec, oldsec, newsec;
	struct Frame* iterator = pA->frames;

	if (pA->frames == 0)
	{
		printf("No frames in the animation\n");
		return;
	}

	printf("Run the Animation\n");
	startsec = oldsec = time(NULL);
	while (iterator)
	{
		newsec = time(NULL);
		if (newsec > oldsec)
		{
			printf("Frame #%d, time = %d sec\n", counter++, newsec - startsec);
			printf("Image file name = %s\n", iterator->fileName);
			iterator = iterator->pNext;
			oldsec = newsec;
		}
	}
}
