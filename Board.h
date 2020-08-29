#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "Piece.h"

using std::vector;
using std::make_shared;
using std::shared_ptr;

class Board
{
public:
	/// <summary> </summary>
	/// <param name="playingAsWhite"> - set this to true if playing from white's perspective </param>
	/// <returns> </returns>
	Board(bool playingAsWhite);

	friend std::ostream& operator<<(std::ostream& os, const Board& b);

	shared_ptr<Piece> pieceAt(int i, int j) const;

	char getArtAt(int i, int j) const;

private:
	bool whiteSide;
	vector<vector<shared_ptr<Piece>>> board;
};

shared_ptr<Piece> Board::pieceAt(int i, int j) const
{
	return board[i][j];
}

char Board::getArtAt(int i, int j) const
{
	shared_ptr<Piece> pHere = pieceAt(i, j);

	// no piece here
	if (pHere == nullptr)
	{
		// if i + j is even, then it's a shaded square
		bool isShadedSquare = (i + j) % 2 == 0;

		// print . if it's shaded
		return isShadedSquare ? '.' : ' ';
	}

	return pHere->getArt();
}

Board::Board(bool playingAsWhite) : whiteSide(playingAsWhite)
{
	// initialize the board with nullptrs
	board.resize(8);
	for (int i = 0; i < 8; i++)
	{
		board[i].resize(8, shared_ptr<Piece>(nullptr));
	}

	board[0][0] = shared_ptr<Piece>(new Rook(!playingAsWhite));
	board[0][1] = shared_ptr<Piece>(new Knight(!playingAsWhite));
	board[0][2] = shared_ptr<Piece>(new Bishop(!playingAsWhite));
	board[0][5] = shared_ptr<Piece>(new Bishop(!playingAsWhite));
	board[0][6] = shared_ptr<Piece>(new Knight(!playingAsWhite));
	board[0][7] = shared_ptr<Piece>(new Rook(!playingAsWhite));

	board[0][3 + (1 && !playingAsWhite)] = shared_ptr<Piece>(new King(!playingAsWhite));
	board[0][4 - (1 && !playingAsWhite)] = shared_ptr<Piece>(new Queen(!playingAsWhite));

	// opposing player pawns
	for (int i = 0; i < 8; i++)
	{
		board[1][i] = shared_ptr<Piece>(new Pawn(!playingAsWhite));
	}

	// player pawns
	for (int i = 0; i < 8; i++)
	{
		board[6][i] = shared_ptr<Piece>(new Pawn(playingAsWhite));
	}

	board[7][0] = shared_ptr<Piece>(new Rook(playingAsWhite));
	board[7][1] = shared_ptr<Piece>(new Knight(playingAsWhite));
	board[7][2] = shared_ptr<Piece>(new Bishop(playingAsWhite));
	board[7][5] = shared_ptr<Piece>(new Bishop(playingAsWhite));
	board[7][6] = shared_ptr<Piece>(new Knight(playingAsWhite));
	board[7][7] = shared_ptr<Piece>(new Rook(playingAsWhite));

	board[7][4 - (1 && playingAsWhite)] = shared_ptr<Piece>(new King(playingAsWhite));
	board[7][3 + (1 && playingAsWhite)] = shared_ptr<Piece>(new Queen(playingAsWhite));
}

std::ostream& operator<<(std::ostream& os, const Board& b)
{
	os << "  +---+---+---+---+---+---+---+---+\n";

	for (int i = 0; i < 8; i++)
	{
		os << (b.whiteSide ? (8 - i) : (i + 1)) << " ";
		for (int j = 0; j < 8; j++)
		{
			os << "| " << b.getArtAt(i, j) << " ";
		}
		os << "|\n";
		os << "  +---+---+---+---+---+---+---+---+\n";
	}
	os << "    A   B   C   D   E   F   G   H\n";

	return os;
}