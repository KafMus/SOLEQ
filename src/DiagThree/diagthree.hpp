#ifndef DIAGTHREE_HPP_UUID_0000
#define DIAGTHREE_HPP_UUID_0000

#include <iostream>
#include <array>
#include <vector>


namespace kfsoleq
{

#ifndef SOLEQ_FLOAT
#define SOLEQ_FLOAT double
#endif

class DiagThree {
private:
        unsigned int size;
        std::array<std::vector<SOLEQ_FLOAT>, 3> diagonals;
        std::vector<SOLEQ_FLOAT> constant_terms;
        std::vector<SOLEQ_FLOAT> roots;
public:
	// Constructors and destructors
	DiagThree(); // Default constructor
	DiagThree(const DiagThree& root_diagThree); // Copy constructor
	DiagThree(DiagThree&& base_diagThree); // Move constructor
	~DiagThree(); // Destructor
        DiagThree(unsigned int size,
                  const std::array<std::vector<SOLEQ_FLOAT>, 3>& diagonals,
                  const std::vector<SOLEQ_FLOAT>& constant_terms);
	
	// Getters and setters
        unsigned int getSize() const { return size; }
        
	// Additional infrastructure
	void print() const;
        void printDiagonals() const;
        void printConstantTerms() const;
        void printRoots() const;
        void solve();
        bool checkDiagonalDomination() const;
        
	
	// Operators overload
	DiagThree& operator = (const DiagThree& root_diagThree); // DiagThree assignment
	DiagThree& operator = (DiagThree&& base_diagThree); // Move assignment
};


}


#endif
