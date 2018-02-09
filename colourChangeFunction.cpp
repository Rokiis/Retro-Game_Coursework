//d.jones
void colourText(WINDOW * winName, string text, int colPair, int yCoord, int xCoord)   //takes the window, some text, the colour pair initialisation number and the two co-ordinates.
{
	wattron(winName, COLOR_PAIR(colPair));      //turns on the colour
	mvwprintw(winName, yCoord, xCoord, text.c_str()); //prints the text (coloured)
	wattroff(winName, COLOR_PAIR(colPair)); //turns off the colour
}
