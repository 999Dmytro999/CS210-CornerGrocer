#ifndef CORNER_GROCER_H
#define CORNER_GROCER_H

#include <string>
#include <unordered_map>
#include <vector>

// Corner Grocer frequency tracker
// Author: Dmytro Sishchuk
// Description: Loads an input file of purchased grocery items, builds a
// frequency table, writes a backup data file, and supports 3 reporting modes.

class CornerGrocer {
public:
    // Construct from an input filename. Throws std::runtime_error on failure.
    explicit CornerGrocer(const std::string& inputFilePath);

    // Write "frequency.dat" (one "Item Count" per line).
    // Returns true on success, false otherwise.
    bool WriteBackup(const std::string& outPath = "frequency.dat") const;

    // Case-insensitive frequency lookup; returns 0 if missing.
    int GetFrequency(const std::string& item) const;

    // Return all items alphabetically with display names and counts.
    // Each pair: {DisplayName, Count}
    std::vector<std::pair<std::string, int>> GetAllFrequenciesSorted() const;

    // Convenience printers (to std::cout).
    void PrintAll() const;          // Menu option 2
    void PrintHistogram() const;    // Menu option 3

private:
    // Normalize keys (lowercase) to make lookups case-insensitive
    static std::string ToLower(const std::string& s);

    // Frequency keyed by lowercase item
    std::unordered_map<std::string, int> counts_;

    // First-seen display name for each lowercase key (keeps capitalization)
    std::unordered_map<std::string, std::string> displayName_;
};

#endif // CORNER_GROCER_H
