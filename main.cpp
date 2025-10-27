#include "CornerGrocer.h"

#include <iostream>
#include <limits>
#include <string>

// Simple, robust integer menu input: 1..4
static int ReadMenuSelection() {
    while (true) {
        std::cout << "\n===== Corner Grocer Menu =====\n"
                  << "1) Item frequency\n"
                  << "2) List all item frequencies\n"
                  << "3) Histogram\n"
                  << "4) Exit\n"
                  << "Select an option (1-4): ";

        int choice{};
        if (std::cin >> choice && choice >= 1 && choice <= 4) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }

        std::cout << "Invalid selection. Please enter 1, 2, 3, or 4.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int main() {
    // Adjust filename if your class/IDE requires a different relative path.
    const std::string kInput = "CS210_Project_Three_Input_File.txt";

    try {
        CornerGrocer grocer(kInput);

        // Create backup data file immediately
        if (!grocer.WriteBackup("frequency.dat")) {
            std::cerr << "Warning: could not write frequency.dat (backup file).\n";
        }

        while (true) {
            int choice = ReadMenuSelection();
            if (choice == 4) {
                std::cout << "Goodbye!\n";
                break;
            }

            switch (choice) {
                case 1: {
                    std::cout << "Enter an item name to search: ";
                    std::string query;
                    std::getline(std::cin, query);
                    int freq = grocer.GetFrequency(query);
                    std::cout << query << " " << freq << "\n";
                    break;
                }
                case 2:
                    grocer.PrintAll();
                    break;
                case 3:
                    grocer.PrintHistogram();
                    break;
                default:
                    // unreachable due to validation
                    break;
            }
        }
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        return 1;
    }

    return 0;
}
