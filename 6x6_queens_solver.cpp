
/*
 * 6x6 Queens Dominating Set Solver
 * Author: [Fabian Giziński]
 * Description: Finds all combinations of 3 queens that cover a 6x6 board using bitboards.
 * Language: C++20
 */


#include <iostream>
#include <vector>
#include <cstdint>
#include <array>

using Bitboard = uint64_t;

constexpr int BOARD_DIM = 6;
constexpr int TOTAL_CELLS = BOARD_DIM * BOARD_DIM;
constexpr uint64_t FULL_BOARD = (1ULL << TOTAL_CELLS) - 1;

std::array<Bitboard, TOTAL_CELLS> queensAttacks{};

/**
 * BITBOARD (6x6):
 * 30 31 32 33 34 35  <- Row 5
 * 24 25 26 27 28 29  <- Row 4
 * 18 19 20 21 22 23  <- Row 3
 * 12 13 14 15 16 17  <- Row 2
 * 6  7  8  9  10 11  <- Row 1
 * 0  1  2  3  4  5   <- Row 0 LSB
 */

void init_queensAttacks(){

    for (int curCell = 0; curCell < TOTAL_CELLS; curCell++) {
        uint64_t pattern = (1ULL<<curCell);
        int row = curCell / BOARD_DIM;
        int col = curCell % BOARD_DIM;

        for (int r = 0; r < BOARD_DIM; r++) {
            for (int c = 0; c < BOARD_DIM; c++) {
                if (r == row && c == col) continue;

                if (r == row || c == col) {
                    pattern |= (1ULL << (r * BOARD_DIM + c));
                }

                if (abs(r - row) == abs(c - col)) {
                    pattern |= (1ULL << (r * BOARD_DIM + c));
                }
            }
        }
        queensAttacks[curCell] = pattern;
    }

}

std::vector<Bitboard> generate_Result() {

    std::vector<Bitboard> Results;

    for (int i = 0; i < TOTAL_CELLS; i++) {
        uint64_t maskI = queensAttacks[i];

        for (int j = i + 1; j < TOTAL_CELLS; j++) {
            uint64_t maskIJ = maskI | queensAttacks[j];

            for (int l = j + 1; l < TOTAL_CELLS; l++) {
                uint64_t maskIJL = maskIJ | queensAttacks[l];

                if (maskIJL== FULL_BOARD){
                    Results.push_back((1ULL<<i)| (1ULL << j) | (1ULL << l));
                }
            }
        }
    }

    return Results;
}

void print_Bitboard(const Bitboard& b) {

    for (int r = 5; r >= 0; r--) {
        for (int c = 0; c < 6; c++) {
            int idx = r * 6 + c;

            if ((b >> idx) & 1ULL) {
                std::cout << "H ";
            }
            else {
                std::cout << "0 ";
            }
        }
        std::cout << "\n";
    }
    std::cout << std::endl; 
}


int main()
{
    init_queensAttacks();
	
    auto Solutions = generate_Result();
    
    for (const auto& s : Solutions){
        print_Bitboard(s);
        std::cout << "\n";
    }


}

