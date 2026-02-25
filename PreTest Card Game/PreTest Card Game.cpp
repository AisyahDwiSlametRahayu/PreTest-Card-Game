#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>

// ==========================
// IModifier (Interface)
// ==========================
class IModifier {
public:
    virtual int apply(int baseScore) = 0;
    virtual ~IModifier() {}
};

// ==========================
// Concrete Modifiers
// ==========================
class DoubleScoreModifier : public IModifier {
public:
    int apply(int baseScore) override {
        return baseScore * 2;
    }
};

class FlatBonusModifier : public IModifier {
public:
    int apply(int baseScore) override {
        return baseScore + 50;
    }
};

// ==========================
// ScoringSystem
// ==========================
class ScoringSystem {
private:
    std::vector<std::shared_ptr<IModifier>> modifiers;

public:
    void addModifier(std::shared_ptr<IModifier> mod) {
        modifiers.push_back(mod);
    }

    int calculateScore(int baseScore) {
        int score = baseScore;

        std::cout << "Base Score: " << score << std::endl;

        for (auto& mod : modifiers) {
            score = mod->apply(score);
        }

        return score;
    }
};

// ==========================
// RunSession
// ==========================
class RunSession {
private:
    ScoringSystem scoring;
    int totalScore = 0;

public:
    void start() {
        std::srand(static_cast<unsigned>(std::time(nullptr)));

        std::cout << "=== Start Run ===\n";

        for (int round = 1; round <= 3; round++) {
            std::cout << "\n--- Round " << round << " ---\n";

            int baseScore = std::rand() % 100 + 1;

            int finalScore = scoring.calculateScore(baseScore);

            std::cout << "Modified Score: " << finalScore << std::endl;

            totalScore += finalScore;

            if (round == 1) {
                std::cout << "Adding DoubleScoreModifier...\n";
                scoring.addModifier(std::make_shared<DoubleScoreModifier>());
            }

            if (round == 2) {
                std::cout << "Adding FlatBonusModifier...\n";
                scoring.addModifier(std::make_shared<FlatBonusModifier>());
            }
        }

        std::cout << "\n=== End Run ===\n";
        std::cout << "Total Score: " << totalScore << std::endl;
    }
};

// ==========================
// main
// ==========================
int main() {
    RunSession session;
    session.start();
    return 0;
}