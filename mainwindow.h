#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QButtonGroup>
#include "Game.h"

// Assuming you have the Game, HumanPlayer, and ComputerPlayer classes ready for integration.

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startNewGameButton_clicked();
    void on_rockButton_clicked();
    void on_paperButton_clicked();
    void on_scissorsButton_clicked();
    void startNewGame();
    void playRound(Move move);
    void updateUI(const Move& playerMove, const Move& computerMove);
    void playRock();
    void playPaper();
    void playScissors();

private:
    void setupUI();
    void connectSignals();

    // Widgets
    QRadioButton *normalComputerButton;
    QRadioButton *smartComputerButton;
    QButtonGroup *computerTypeGroup;
    QSpinBox *roundsSpinBox;
    QPushButton *startNewGameButton;
    QPushButton *rockButton;
    QPushButton *paperButton;
    QPushButton *scissorsButton;
    QLabel *roundInfoLabel;
    QLabel *humanChoiceLabel;
    QLabel *computerChoiceLabel;
    QLabel *winnerLabel;
    QLabel *humanWinsLabel;
    QLabel *computerWinsLabel;
    QLabel *tiesLabel;

    // Layouts
    QVBoxLayout *mainLayout;
    QHBoxLayout *computerTypeLayout;
    QHBoxLayout *controlsLayout;
    QHBoxLayout *actionsLayout;
    QVBoxLayout *infoLayout;

    // Game logic classes
    Game *game;
    HumanPlayer *humanPlayer;
    ComputerPlayer *computerPlayer;
};

#endif // MAINWINDOW_H
