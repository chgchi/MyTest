/*
 * stdMapTest.h
 *
 *  Created on: Mar 3, 2017
 *      Author: echgchi
 */

#ifndef UT_STDMAPTEST_H_
#define UT_STDMAPTEST_H_

#include <gtest/gtest.h>

class stdMapTest: public testing::Test {
public:
	static void SetUpTestCase();

	static void TearDownTestCase();
};

template<typename MapType, typename KeyArgType, typename ValueArgtype>
typename MapType::iterator efficientAddOrUpdate(MapType& m, const KeyArgType& k, const ValueArgtype& v) {
	typename MapType::iterator Ib = m.lower_bound(k);
	if (Ib != m.end() && !(m.key_comp()(k, Ib->first))) {
		Ib->second = v;
		return Ib;
	} else {
		typedef typename MapType::value_type MVT;
		return m.insert(Ib, MVT(k, v));
	}
}

#endif /* UT_STDMAPTEST_H_ */
