#include "CornerGrocer.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <stdexcept>

// --- helpers ---
std::string CornerGrocer::ToLower(const std::string& s) {
    std::string out;
    out.reserve(s.size());
    for (unsigned char ch : s) out.push_back(static_cast<char>(std::tolower(ch)));
    return out;
}

// --- ctor: load file and build frequency table ---
CornerGrocer::CornerGrocer(const std::string& inputFilePath) {
    std::ifstream in(inputFilePath);
    if (!in) {
        throw std::runtime_error("Unable to open input file: " + inputFilePath);
    }

    std::string item;
    // Each line contains one item (word)
    while (std::getline(in, item)) {
        if (item.empty()) continue;
        std::string key = ToLower(item);
        ++counts_[key];
        // Preserve the first-seen "pretty" capitalization for display
        if (displayName_.find(key) == displayName_.end()) {
            displayName_[key] = item;
        }
    }
}

// --- write backup file ---
bool CornerGrocer::WriteBackup(const std::string& outPath) const {
    std::ofstream out(outPath, std::ios::trunc);
    if (!out) return false;

    // Sorted for stable output (alphabetical by display name)
    auto rows = GetAllFrequenciesSorted();
    for (const auto& row : rows) {
        out << row.first << ' ' << row.second << '\n';
    }
    return true;
}

// --- frequency lookup ---
int CornerGrocer::GetFrequency(const std::string& item) const {
    auto it = counts_.find(ToLower(item));
    return (it == counts_.end()) ? 0 : it->second;
}

// --- sorted list for printing ---
std::vector<std::pair<std::string, int>> CornerGrocer::GetAllFrequenciesSorted() const {
    std::vector<std::pair<std::string, int>> rows;
    rows.reserve(counts_.size());
    for (const auto& kv : counts_) {
        const std::string& key = kv.first;
        int count = kv.second;
        auto found = displayName_.find(key);
        const std::string& pretty = (found == displayName_.end()) ? key : found->second;
        rows.emplace_back(pretty, count);
    }
    std::sort(rows.begin(), rows.end(),
              [](const auto& a, const auto& b) { return a.first < b.first; });
    return rows;
}

// --- printers ---
void CornerGrocer::PrintAll() const {
    auto rows = GetAllFrequenciesSorted();
    for (const auto& row : rows) {
        std::cout << row.first << ' ' << row.second << '\n';
    }
}

void CornerGrocer::PrintHistogram() const {
    auto rows = GetAllFrequenciesSorted();
    for (const auto& row : rows) {
        std::cout << row.first << ' ';
        for (int i = 0; i < row.second; ++i) std::cout << '*';
        std::cout << '\n';
    }
}
