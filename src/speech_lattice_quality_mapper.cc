#include "speech_lattice_quality_mapper.h"

#include <iostream>

#include "absl/base/internal/raw_logging.h"
#include "absl/status/status.h"

namespace Visqol {
absl::Status SpeechLatticeQualityMapper::Init() {
  this->model_ =
      std::make_unique<Visqol::DeepLatticeNetwork::MediumSpeechModel>();
  return absl::Status();
}

double SpeechLatticeQualityMapper::PredictQuality(
    const std::vector<double>& fvnsim_vector,
    const std::vector<double>& fstdnsim_vector,
    const std::vector<double>& fvdegenergy_vector) const {
  // Set the value for tau (the median quantile).
  *model_->arg0_data() = .5;

  ABSL_RAW_CHECK(fvnsim_vector.size() == 21,
                 "fvnsim size must be 21 to match the saved model.");
  ABSL_RAW_CHECK(fstdnsim_vector.size() == 21,
                 "fstdnsim size must be 21 to match the saved model.");
  ABSL_RAW_CHECK(fvdegenergy_vector.size() == 21,
                 "fdegenergy size must be 21 to match the saved model.");

  // Set values for 21 FVNSIM features, 21 FSTDNSIM, and 21 FVDEGENERGY input
  // features.
  // Unfortunately, the tfcompile generated functions do not allow indexing, so
  // lets construct our own indexed std::vector to set the data.
  std::vector<float *> fvnsim_arg_pointers{
      model_->arg1_data(),  model_->arg2_data(),  model_->arg3_data(),
      model_->arg4_data(),  model_->arg5_data(),  model_->arg6_data(),
      model_->arg7_data(),  model_->arg8_data(),  model_->arg9_data(),
      model_->arg10_data(), model_->arg11_data(), model_->arg12_data(),
      model_->arg13_data(), model_->arg14_data(), model_->arg15_data(),
      model_->arg16_data(), model_->arg17_data(), model_->arg18_data(),
      model_->arg19_data(), model_->arg20_data(), model_->arg21_data()};

  std::vector<float *> fstdnsim_arg_pointers{
      model_->arg22_data(), model_->arg23_data(), model_->arg24_data(),
      model_->arg25_data(), model_->arg26_data(), model_->arg27_data(),
      model_->arg28_data(), model_->arg29_data(), model_->arg30_data(),
      model_->arg31_data(), model_->arg32_data(), model_->arg33_data(),
      model_->arg34_data(), model_->arg35_data(), model_->arg36_data(),
      model_->arg37_data(), model_->arg38_data(), model_->arg39_data(),
      model_->arg40_data(), model_->arg41_data(), model_->arg42_data()};

  std::vector<float *> fvdegenergy_arg_pointers{
      model_->arg43_data(), model_->arg44_data(), model_->arg45_data(),
      model_->arg46_data(), model_->arg47_data(), model_->arg48_data(),
      model_->arg49_data(), model_->arg50_data(), model_->arg51_data(),
      model_->arg52_data(), model_->arg53_data(), model_->arg54_data(),
      model_->arg55_data(), model_->arg56_data(), model_->arg57_data(),
      model_->arg58_data(), model_->arg59_data(), model_->arg60_data(),
      model_->arg61_data(), model_->arg62_data(), model_->arg63_data()};

  // Set the value for each of the pointers.
  for (int i = 0; i < fvnsim_arg_pointers.size(); i++) {
    *fvnsim_arg_pointers[i] = fvnsim_vector[i];
  }

  for (int i = 0; i < fstdnsim_arg_pointers.size(); i++) {
    *fstdnsim_arg_pointers[i] = fstdnsim_vector[i];
  }

  for (int i = 0; i < fvdegenergy_arg_pointers.size(); i++) {
    *fvdegenergy_arg_pointers[i] = fvdegenergy_vector[i];
  }

  model_->Run();

  return model_->result0(0, 0);
}

}  // namespace Visqol
