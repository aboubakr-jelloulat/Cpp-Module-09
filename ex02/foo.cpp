#include "PmergeMe.hpp"

std::deque<int> JacobsthalSeqDeq( size_t size )
{
	std::deque<int> jacobSeq;
	size_t prev2 = 0, prev1 = 1, curr = 0;

	jacobSeq.push_back(prev2);
	if (size == 0) return jacobSeq;
	if (size >= 1) jacobSeq.push_back(prev1);

	while (true) {
		curr = prev1 + 2 * prev2;
		if (curr > size)
			break;
		jacobSeq.push_back(curr);
		prev2 = prev1;
		prev1 = curr;
	}
	return jacobSeq;
}

std::deque<int> insertIndexesDeq( size_t size ) {
	std::deque<int> indexes;

	indexes = JacobsthalSeqDeq( size );
	std::deque<int>::iterator it = indexes.begin() + 1;
	while (it != indexes.end()) {
		*it -= 1;
		++it;
	}
	
	std::deque<int> uniqueIndexes;
	std::deque<int>::iterator _it = indexes.begin();
	while (_it != indexes.end()) {
		if (std::find(uniqueIndexes.begin(), uniqueIndexes.end(), *_it) == uniqueIndexes.end())
			uniqueIndexes.push_back(*_it);
		++_it;
	}
	indexes = uniqueIndexes;

	for(size_t i=0; i<size; i++) {
		if (std::find(indexes.begin(), indexes.end(), i) == indexes.end())
			indexes.push_back(i);
	}

	return indexes;
}

std::deque<int> fordJohnsonDeq( std::deque<int>& seq ) {
	if (seq.size() < 2)
		return seq;
	
	std::deque<int> a,b,sorted;

	for (size_t i=0; i<seq.size(); i+=2) {
		if (i + 1 < seq.size()) {
			int larger = std::max(seq[i], seq[i+1]);
			int smaller = std::min(seq[i], seq[i+1]);

			a.push_back(larger);
			b.push_back(smaller);
		} else
			b.push_back(seq[i]);
	}

	sorted = fordJohnsonDeq(a);
	
	std::deque<int> indexes = insertIndexesDeq(b.size());

	for (size_t i=0; i<indexes.size(); ++i) {
		std::deque<int>::iterator _it = std::lower_bound(sorted.begin(), sorted.end(), b[indexes[i]]);
		sorted.insert(_it, b[indexes[i]]);
	}

	return sorted;
}

