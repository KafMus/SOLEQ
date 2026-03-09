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
        std::array<std::vector<soleq_float>, 3> diagonals;
        std::vector<soleq_float> constant_terms;
        std::vector<soleq_float> roots;
public:
	// Constructors and destructors
	DiagThree(); // Default constructor
        DiagThree(size_t given_size,
                  const std::array<std::vector<soleq_float>, 3>& given_diagonals,
                  const std::vector<soleq_float>& given_constant_terms);
	
	// Getters and setters
        size_t getSize() const { return size; }
        const std::array<std::vector<soleq_float>, 3>& getDiagonals() const { return diagonals; }
        const std::vector<soleq_float>& getConstantTerms() const { return constant_terms; }
        const std::vector<soleq_float>& getRoots() const { return roots; }
        
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
