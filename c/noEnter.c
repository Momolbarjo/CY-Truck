#include <stdio.h>
#include <termios.h>

char getch() {
    char buf = 0;
    struct termios old = {0};

    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    // Get the terminal attributes for the standard input (0) and store them in the old struct.
    // If tcgetattr() returns a value less than 0, an error occurred, and perror() prints an error message.

    old.c_lflag &= ~ICANON;// Disable canonical mode in the local flags of the terminal attributes.
    old.c_lflag &= ~ECHO;  // Disable echoing of input characters in the local flags of the terminal attributes.
    old.c_cc[VMIN] = 1;// Set the minimum number of characters to read to 1.
    old.c_cc[VTIME] = 0;// Set the timeout in tenths of a second to 0.

    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");// Set the terminal attributes for the standard input (0) to the modified attributes stored in the old struct.

    if (read(0, &buf, 1) < 0)
        perror ("read()"); // Read a single character from the standard input (0) and store it in the buf variable.

    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;

    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror ("tcsetattr ~ICANON");// Set the terminal attributes for the standard input (0) to the modified attributes stored in the old struct.

    return buf;
}

int main(void){

	char c=getch();
	
	return 0;
}
