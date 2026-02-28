#ifndef DIAGTHREE_HPP_UUID_0000
#define DIAGTHREE_HPP_UUID_0000

#include <SOLEQ/DEFINES.hpp>
#include <array>
#include <vector>


namespace kfsoleq
{

class DiagThree {
private:
        size_t size;
        std::array<std::vector<SOLEQ_FLOAT>, 3> diagonals;
        std::vector<SOLEQ_FLOAT> constant_terms;
        std::vector<SOLEQ_FLOAT> roots;
public:
	// Constructors and destructors
	DiagThree(); // Default constructor
        DiagThree(size_t given_size,
                  const std::array<std::vector<SOLEQ_FLOAT>, 3>& given_diagonals,
                  const std::vector<SOLEQ_FLOAT>& given_constant_terms);
	
	// Getters and setters
        size_t getSize() const { return size; }
        std::array<std::vector<SOLEQ_FLOAT>, 3> getDiagonals() const { return diagonals; }
        std::vector<SOLEQ_FLOAT> getConstantTerms() const { return constant_terms; }
        std::vector<SOLEQ_FLOAT> getRoots() const { return roots; }
        
	// Additional infrastructure
	void print() const;
        void printDiagonals() const;
        void printConstantTerms() const;
        void printRoots() const;
        void solve();
        bool checkDiagonalDomination() const;
};


}


#endif
