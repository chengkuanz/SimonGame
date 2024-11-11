#include "SimonGame.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include <random>
#include <SFML/Audio.hpp>
//Chengkuan Zhao
//last modified: 2023 September 8
using namespace std;
std::vector<int> sequence;
bool startFlashing = false;
bool continueFlashing = false;
bool redButtonPressed = false;
bool greenButtonPressed = false;
bool blueButtonPressed = false;
bool yellowButtonPressed = false;
int userPressColorbutonCount = 0;
int whichBottonToFlashing = 0;
bool userPressColorButtonCorrrectness = false;
bool gameOver = false;
bool quitGame = false;
bool timeOver = false;
bool gameIsRunning = false; 

// check if user press the correct color button
void checkUserPressColorButtonCorrectness(int colorIndex) {
	if (userPressColorbutonCount <= sequence.size()) {
		if (sequence[userPressColorbutonCount - 1] == colorIndex) {
			printf("correct\n");
			if (userPressColorbutonCount == sequence.size()) {
				//printf("you made it to round %d\n", userPressColorbutonCount);
				continueFlashing = true;
			sf::Music soundSuccess;
			soundSuccess.openFromFile("success.ogg");// put sound file in the same folder as the .exe file 
			//3 seconds sound
			soundSuccess.play();
			while (soundSuccess.getStatus() == sf::SoundSource::Playing) {
				sf::sleep(sf::milliseconds(100));
			}
			
						}
			//continueFlashing = true;
		}
		else {
			printf("wrong, please restart game \n");
			printf("you made it to round %I64u\n", sequence.size() - 1);
			sf::Music failSuccess;
			failSuccess.openFromFile("fail.ogg");// put sound file in the same folder as the .exe file 
			// 5 seconds sound
			failSuccess.play();
			while (failSuccess.getStatus() == sf::SoundSource::Playing) {
				sf::sleep(sf::milliseconds(200));
			}
			gameOver = true;
		}
	}
	else {
		printf("out of range, please restart game\n");
		printf("you made it to round %I64u\n", sequence.size() - 1);
	}

}



// main function
int main() {
	// Create the main window
	sf::Clock clock;
	sf::Clock timer;
	sf::RenderWindow window(sf::VideoMode(800, 600), "Simon game created by Chengkuan using TGUI & SFML ");// 
	tgui::Gui gui(window); // Create the gui and attach it to the window
	gui.loadWidgetsFromFile("form.txt");// Load the widgets from the form file

	// Get the pointers to the widgets
	auto redButton = gui.get<tgui::Button>("redButton");
	auto greenButton = gui.get<tgui::Button>("greenButton");
	auto blueButton = gui.get<tgui::Button>("blueButton");
	auto yellowButton = gui.get<tgui::Button>("yellowButton");
	auto startButton = gui.get<tgui::Button>("startButton");
	auto gameOverLabel = gui.get<tgui::Label>("gameOverLabel");
	auto chatBox = gui.get<tgui::ChatBox>("chatBox");
	auto quitBotton = gui.get<tgui::Button>("quitBotton");

	// Set the background color of the buttons
	redButton->getRenderer()->setBackgroundColor(sf::Color::Red);
	greenButton->getRenderer()->setBackgroundColor(sf::Color::Green);
	blueButton->getRenderer()->setBackgroundColor(sf::Color::Blue);
	yellowButton->getRenderer()->setBackgroundColor(sf::Color::Yellow);


	//
	std::random_device rd;
	// Initialize Mersenne Twister pseudo-random number generator
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, 3);


	// Connect the button callbacks
	quitBotton->onPress([&]() {
		quitGame = !quitGame;
	timer.restart();
	gameOver = false;
	timeOver = false;
		});


	startButton->onPress([&]() {
		startFlashing = !startFlashing;
	gameIsRunning = true;
	timer.restart();
		});
	redButton->onPress([&]() {
		printf("red button pressed\n");
	redButtonPressed = true;
	timer.restart();
		});

	greenButton->onPress([&]() {
		printf("green button pressed\n");
	greenButtonPressed = true;
	timer.restart();
		});

	blueButton->onPress([&]() {
		printf("blue button pressed\n");
	blueButtonPressed = true;
	timer.restart();
		});

	yellowButton->onPress([&]() {
		printf("yellow button pressed\n");
	yellowButtonPressed = true;
	timer.restart();
		});


	int flashingCounter = 0;

	// Start the game loop
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			gui.handleEvent(event);
		}

		// Clear the window with white background
		window.clear(sf::Color::White);


		if (startFlashing || continueFlashing) {


			flashingCounter++;
			//print flashingcounter
			printf("\ngoing to flashing%d    ", flashingCounter);


			if (startFlashing) {
				gameOver = false;
				timeOver = false;
				gameIsRunning = true;
				printf(" start flashining");
				chatBox->addLine("\n\n\n\n");
				sequence.clear();
				int randomIndex = distrib(gen);
				sequence.push_back(randomIndex);
				whichBottonToFlashing = randomIndex;
				userPressColorbutonCount = 0;
				startFlashing = false;
				flashingCounter = 0;
				timer.restart();
				
			}
			else if (continueFlashing && flashingCounter <= sequence.size()) {
				printf("continue flashing but not reached the end of existing sequence");
				whichBottonToFlashing = sequence[flashingCounter - 1];
				timer.restart();
			}
			else
			{
				printf("continue flashing, a new one");
				int randomIndex = 0;


				do {
					randomIndex = distrib(gen);
				} while (randomIndex == sequence[sequence.size() - 1]);

				sequence.push_back(randomIndex);

				whichBottonToFlashing = randomIndex;
				continueFlashing = false;
				flashingCounter = 0;
				userPressColorbutonCount = 0;
				timer.restart();
			}

			//print the sequence vector
			printf("sequence vector is: ");
			for (int i = 0; i < sequence.size(); i++) {
				printf("%d", sequence[i]);
			}
			printf("\n");

			switch (whichBottonToFlashing) {
			case 0:
				redButton->getRenderer()->setBackgroundColor(sf::Color::Cyan);
				gui.draw(); window.display();
				sf::sleep(sf::milliseconds(500));
				redButton->getRenderer()->setBackgroundColor(sf::Color::Red);
				break;
			case 1:
				greenButton->getRenderer()->setBackgroundColor(sf::Color::Magenta);
				gui.draw(); window.display();
				sf::sleep(sf::milliseconds(500));
				greenButton->getRenderer()->setBackgroundColor(sf::Color::Green);
				break;
			case 2:
				blueButton->getRenderer()->setBackgroundColor(sf::Color::Magenta);
				gui.draw(); window.display();
				sf::sleep(sf::milliseconds(500));
				blueButton->getRenderer()->setBackgroundColor(sf::Color::Blue);
				break;
			case 3:
				yellowButton->getRenderer()->setBackgroundColor(sf::Color::Cyan);
				gui.draw(); window.display();
				sf::sleep(sf::milliseconds(500));
				yellowButton->getRenderer()->setBackgroundColor(sf::Color::Yellow);
				break;
			}
			//startFlashing = false;
			//continueFlashing = false;
		}

		if (redButtonPressed) {
			redButton->getRenderer()->setBackgroundColor(sf::Color::White);
			gui.draw(); window.display();
			sf::sleep(sf::milliseconds(500));
			redButton->getRenderer()->setBackgroundColor(sf::Color::Red);
			userPressColorbutonCount++;
			printf("userPressColorbutonCount%d    ", userPressColorbutonCount);
			redButtonPressed = false;
			checkUserPressColorButtonCorrectness(0);
			timer.restart();

		}

		if (greenButtonPressed) {
			greenButton->getRenderer()->setBackgroundColor(sf::Color::White);
			gui.draw(); window.display();
			sf::sleep(sf::milliseconds(500));
			greenButton->getRenderer()->setBackgroundColor(sf::Color::Green);
			userPressColorbutonCount++;
			printf("userPressColorbutonCount%d    ", userPressColorbutonCount);
			greenButtonPressed = false;
			checkUserPressColorButtonCorrectness(1);
			timer.restart();
		}

		if (blueButtonPressed) {
			blueButton->getRenderer()->setBackgroundColor(sf::Color::White);
			gui.draw(); window.display();
			sf::sleep(sf::milliseconds(500));
			blueButton->getRenderer()->setBackgroundColor(sf::Color::Blue);
			userPressColorbutonCount++;
			printf("userPressColorbutonCount%d    ", userPressColorbutonCount);
			blueButtonPressed = false;
			checkUserPressColorButtonCorrectness(2);
			timer.restart();
		}

		if (yellowButtonPressed) {
			yellowButton->getRenderer()->setBackgroundColor(sf::Color::White);
			gui.draw(); window.display();
			sf::sleep(sf::milliseconds(500));
			yellowButton->getRenderer()->setBackgroundColor(sf::Color::Yellow);
			userPressColorbutonCount++;
			printf("userPressColorbutonCount%d    ", userPressColorbutonCount);
			yellowButtonPressed = false;
			checkUserPressColorButtonCorrectness(3);
			timer.restart();
		}

		if (startFlashing == false && redButtonPressed == false && greenButtonPressed == false && blueButtonPressed == false && yellowButtonPressed == false) {
			// printf (" game over");
		}


		if (timer.getElapsedTime().asSeconds() > 5.0f) {
			timeOver = true;
			timer.restart();
		}

		
		if (gameOver == true && gameIsRunning == true) {
			//gameOverLabel->setText("Sorry wrong color pressed, you made it to round " + to_string(sequence.size()-1));
			chatBox->addLine("Sorry wrong color pressed, you made it to round " + to_string(sequence.size() - 1));
			chatBox->addLine("Press START/RESTART to start again, or press the QUIT button to exit\n");
			gameIsRunning = false;
			gameOver = false;
			timeOver = false;
			timer.restart();
			
		}
		
		if (timeOver == true && gameIsRunning == true){
			chatBox->addLine("Time's up! You made it to round " + to_string(sequence.size() - 1));
			chatBox->addLine("Press START/RESTART to start again, or press the QUIT button to exit\n");
			timeOver = false;
			gameIsRunning = false;
			timeOver = false;
			timer.restart();
		}

		if (quitGame == true) {
			window.close();
			
		}




		gui.draw();
		window.display();
	}

	return 0;
}


