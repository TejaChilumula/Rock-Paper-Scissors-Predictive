#include "mainwindow.h"
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUI();
    connectSignals();
}

MainWindow::~MainWindow() {
    // Clean up any pointers if you have created them using new
    // Since we're not using smart pointers, you need to delete them manually
    delete game;
    delete humanPlayer;
    delete computerPlayer;
}

void MainWindow::setupUI() {
    // Create the widgets
    normalComputerButton = new QRadioButton(tr("Normal Computer"), this);
    smartComputerButton = new QRadioButton(tr("Smart Computer"), this);
    roundsSpinBox = new QSpinBox(this);
    startNewGameButton = new QPushButton(tr("Start New Game"), this);
    rockButton = new QPushButton(tr("Rock"), this);
    paperButton = new QPushButton(tr("Paper"), this);
    scissorsButton = new QPushButton(tr("Scissors"), this);
    roundInfoLabel = new QLabel(tr("Round: 0"), this);
    humanChoiceLabel = new QLabel(tr("Human chooses: "), this);
    computerChoiceLabel = new QLabel(tr("Computer chooses: "), this);
    winnerLabel = new QLabel(tr("The winner: "), this);
    humanWinsLabel = new QLabel(tr("Human wins: 0"), this);
    computerWinsLabel = new QLabel(tr("Computer wins: 0"), this);
    tiesLabel = new QLabel(tr("Ties: 0"), this);

    // Create a button group for the computer type radio buttons
    QButtonGroup *computerTypeGroup = new QButtonGroup(this);
    computerTypeGroup->addButton(normalComputerButton);
    computerTypeGroup->addButton(smartComputerButton);
    smartComputerButton->setChecked(true);

    // Set properties for other widgets
    roundsSpinBox->setRange(1, 99);
    roundsSpinBox->setValue(20);

    // Create layouts
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout *computerTypeLayout = new QHBoxLayout();
    QHBoxLayout *controlsLayout = new QHBoxLayout();
    QHBoxLayout *actionsLayout = new QHBoxLayout();
    QVBoxLayout *infoLayout = new QVBoxLayout();

    // Add widgets to layouts
    computerTypeLayout->addWidget(normalComputerButton);
    computerTypeLayout->addWidget(smartComputerButton);
    controlsLayout->addWidget(roundsSpinBox);
    controlsLayout->addWidget(startNewGameButton);
    actionsLayout->addWidget(rockButton);
    actionsLayout->addWidget(paperButton);
    actionsLayout->addWidget(scissorsButton);
    infoLayout->addWidget(roundInfoLabel);
    infoLayout->addWidget(humanChoiceLabel);
    infoLayout->addWidget(computerChoiceLabel);
    infoLayout->addWidget(winnerLabel);
    infoLayout->addWidget(humanWinsLabel);
    infoLayout->addWidget(computerWinsLabel);
    infoLayout->addWidget(tiesLabel);

    // Add sub-layouts to the main layout
    mainLayout->addLayout(computerTypeLayout);
    mainLayout->addLayout(controlsLayout);
    mainLayout->addLayout(actionsLayout);
    mainLayout->addLayout(infoLayout);

    // Set the central widget
    QWidget *centralWidget = new QWidget();
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

void MainWindow::playRock() {
    playRound(Move::ROCK);
}

void MainWindow::playPaper() {
    playRound(Move::PAPER);
}

void MainWindow::playScissors() {
    playRound(Move::SCISSORS);
}


void MainWindow::connectSignals() {
    // Example connection of signals to slots
    connect(startNewGameButton, &QPushButton::clicked, this, &MainWindow::startNewGame);
    // Connect other signals and slots as required
    connect(rockButton, &QPushButton::clicked, this, &MainWindow::playRock);
    connect(paperButton, &QPushButton::clicked, this, &MainWindow::playPaper);
    connect(scissorsButton, &QPushButton::clicked, this, &MainWindow::playScissors);
}

void MainWindow::startNewGame() {
    // Instantiate or reset the game logic
    if (game != nullptr) {
        delete game;
    }
    game = new Game(humanPlayer, computerPlayer);

    // Reset the UI elements
    roundInfoLabel->setText(tr("Round: 0"));
    humanWinsLabel->setText(tr("Human wins: 0"));
    computerWinsLabel->setText(tr("Computer wins: 0"));
    tiesLabel->setText(tr("Ties: 0"));
    humanChoiceLabel->setText(tr("Human chooses: "));
    computerChoiceLabel->setText(tr("Computer chooses: "));
    winnerLabel->setText(tr("The winner: "));
}

void MainWindow::playRound(Move playerMove) {
    if (!game) { // Make sure the game instance exists
        return;
    }

    // Let's assume the computer player also decides on its move here
    Move computerMove = computerPlayer->makeMove();

    // Now we play the round with both moves
    game->playRound(playerMove, computerMove);

    // Update the UI with the results
    updateUI();
}

// The updateUI function that updates the UI based on the latest state of the game
void MainWindow::updateUI() {
    if (!game) { // Make sure the game instance exists
        return;
    }

    // Let's assume these getter methods are now implemented in the Game class
    int round = game->getCurrentRound();
    int humanWins = game->getHumanWins();
    int computerWins = game->getComputerWins();
    int ties = game->getTies();

    roundInfoLabel->setText(tr("Round: ") + QString::number(round));
    humanWinsLabel->setText(tr("Human wins: ") + QString::number(humanWins));
    computerWinsLabel->setText(tr("Computer wins: ") + QString::number(computerWins));
    tiesLabel->setText(tr("Ties: ") + QString::number(ties));

    // You also need to update the choices and winner labels, assuming you have methods to get them
    // For example:
    humanChoiceLabel->setText(tr("Human chooses: ") + QString::fromStdString(game->getLastHumanMove().toString()));
    computerChoiceLabel->setText(tr("Computer chooses: ") + QString::fromStdString(game->getLastComputerMove().toString()));
    winnerLabel->setText(tr("The winner: ") + QString::fromStdString(game->getLastWinner()));
}
