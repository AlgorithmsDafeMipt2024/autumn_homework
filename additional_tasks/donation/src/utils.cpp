#include "utils.hpp"

bool BloodGroup::operator>>(const BloodGroup& another) {
  // Check Rh factor compatibility
  bool rh_compatible = true;

  switch (this->rh_factor_) {
    case RhFactor::Negative:
      break;
    case RhFactor::Positive:
      rh_compatible = (another.rh_factor_ == RhFactor::Positive);
      break;
  }

  // Check ABO blood type compatibility
  bool abo_compatible = true;

  switch (this->blood_type_) {
    case BloodType::O:  // O is a universal donor
      break;
    case BloodType::A:
      abo_compatible = (another.blood_type_ == BloodType::A ||
                        another.blood_type_ == BloodType::AB);
      break;
    case BloodType::B:
      abo_compatible = (another.blood_type_ == BloodType::B ||
                        another.blood_type_ == BloodType::AB);
      break;
    case BloodType::AB:
      abo_compatible =
          (another.blood_type_ == BloodType::AB);  // AB can only donate to AB
      break;
  }
  return rh_compatible && abo_compatible;
}

bool BloodExchange::MatchingUtil(std::size_t human_id,
                                 std::vector<bool>& matched,
                                 std::vector<std::size_t>& matching) {
  for (auto& other : vertices_[human_id]->adjacent) {
    std::size_t other_id = (other)->data;
    std::size_t other_index = Find(other_id);
    if (!matched[other_index]) {
      matched[other_index] = true;
      if (matching[other_index] == vertices_.size() ||
          MatchingUtil(matching[other_index], matched, matching)) {
        matching[other_index] = human_id;
        return true;
      }
    }
  }
  return false;
}

std::size_t BloodExchange::FindMaxMatching() {
  for (std::size_t i = 0; i < vertices_.size(); ++i)
    if (vertices_[i]->role == Role::Donor)
      for (std::size_t j = 0; j < vertices_.size(); ++j)
        if (vertices_[j]->role == Role::Recipient)
          if (vertices_[i]->blood_group >> vertices_[j]->blood_group)
            AddDirEdge(i, j);
          else {
            RemoveDirEdge(i, j);
          }

  std::vector<std::size_t> matching(vertices_.size(), vertices_.size());
  std::size_t result = 0;

  for (std::size_t vertex = 0; vertex < vertices_.size(); ++vertex) {
    std::vector<bool> matched(vertices_.size(), false);
    if (MatchingUtil(vertex, matched, matching)) {
      result++;
    }
  }
  return result;
}