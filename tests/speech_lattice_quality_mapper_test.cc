#include "speech_lattice_quality_mapper.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "machine_learning.h"

namespace Visqol {
namespace {

TEST(SpeechLatticeQualityMapperTest, PredictMLObservationGood) {
  Visqol::SpeechLatticeQualityMapper model;

  ASSERT_TRUE(model.Init().ok());

  // Make a fake observation with high similarity.
  std::vector<double> good_fvnsim(21, 1.0);
  std::vector<double> good_fstdnsim(21, 1.0);
  std::vector<double> good_fvdegenergy(21, 1.0);
  double good_mos =
      model.PredictQuality(good_fvnsim, good_fstdnsim, good_fvdegenergy);

  // A perfect similarity MOS should be above 3.0 for any reasonable model.
  EXPECT_GT(good_mos, 3.0);
  // 5.0 is the maximum score.
  EXPECT_LE(good_mos, 5.0);
}

TEST(SpeechLatticeQualityMapperTest, PredictMLObservationBad) {
  Visqol::SpeechLatticeQualityMapper model;

  ASSERT_TRUE(model.Init().ok());
  // Test an observation with poor quality (0.0 is bad quality).
  std::vector<double> bad_fvnsim(21, 0.0);
  std::vector<double> bad_fstdnsim(21, 0.0);
  std::vector<double> bad_fvdegenergy(21, 0.0);

  double bad_mos =
      model.PredictQuality(bad_fvnsim, bad_fstdnsim, bad_fvdegenergy);

  // A zero similarity MOS should be below 3.0 for any reasonable model.
  EXPECT_LT(bad_mos, 3.0);
  // 1.0 is the minimum score.
  EXPECT_GE(bad_mos, 1.0);
}

TEST(SpeechLatticeQualityMapperTest, FailsOnIllegalSize) {
  Visqol::SpeechLatticeQualityMapper model;

  ASSERT_TRUE(model.Init().ok());

  // Make a fake observation with high similarity.
  std::vector<double> good_fvnsim(21, 1.0);
  std::vector<double> illegal_fstdnsim(19, 1.0);
  std::vector<double> good_fvdegenergy(21, 1.0);
  EXPECT_DEATH(
      model.PredictQuality(good_fvnsim, illegal_fstdnsim, good_fvdegenergy),
      "fstdnsim size must be 21 to match the saved model.");
}

}  // namespace
}  // namespace Visqol
