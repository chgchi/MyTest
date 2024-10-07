
#include <vector>
#include <memory>
#include <unordered_map>
#include <gtest/gtest.h>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int> &nums, int target) {
        unordered_map<int, int> hashTab;
        for(int i=0; i<nums.size(); i++){
            auto diff = target - nums[i];
            auto res = hashTab.find(diff);
            if(res != hashTab.end()){
                return {res->second, i };
            }
            hashTab[diff] = i;
        }
        return {};
    }
};

class LeleTest1 : public testing::Test {
  protected:
     virtual void SetUp()
     {
        solutionPtr_ = std::make_shared<Solution>();
     }
     virtual void TearDown()
     {
        solutionPtr_.reset();
     }
 
    std::shared_ptr<Solution> solutionPtr_;
};


// ./testAlgorithms --gtest_filter=LeleTest1.twoSum
TEST_F(LeleTest1, twoSum){

    std::vector<int> vec{2,7,11,15};
    auto res = solutionPtr_->twoSum(vec, 9);
    ASSERT_EQ(2, res.size());
    ASSERT_EQ(2, res[0]);
    ASSERT_EQ(7, res[1]);
    system("pause");
}