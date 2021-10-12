/*
 * Copyright 2021 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef THIRD_PARTY_VISQOL_SRC_SPEECH_LATTICE_LATTICE_QUALITY_MAPPER_H_
#define THIRD_PARTY_VISQOL_SRC_SPEECH_LATTICE_LATTICE_QUALITY_MAPPER_H_

#include "absl/status/status.h"
#include "speech_lattice_compiled_graph.h"  // generated
#include "file_path.h"
#include "similarity_to_quality_mapper.h"

namespace Visqol {

/**
 * This class represents a deep lattice network model quality mapper.
 * Typically, the model is trained in python and stored in the SavedModel
 * tensorflow format.  This class loads the model and contains the tensorflow
 * specific code to run inference using the model given audio features.
 */
class SpeechLatticeQualityMapper : public SimilarityToQualityMapper {
 public:
  SpeechLatticeQualityMapper() = default;
  absl::Status Init() override;

  double PredictQuality(
      const std::vector<double>& fvnsim_vector,
      const std::vector<double>& fstdnsim_vector,
      const std::vector<double>& fvdegenergy_vector) const override;

 private:
  std::unique_ptr<Visqol::DeepLatticeNetwork::MediumSpeechModel> model_;
};

}  // namespace Visqol

#endif  // THIRD_PARTY_VISQOL_SRC_SPEECH_LATTICE_LATTICE_QUALITY_MAPPER_H_
