#pragma once

#include <cmath>

#include "graph.hpp"

/// @brief Enum of blood groups
enum BloodType { O, A, B, AB };

/// @brief Enum of Rh factor
enum RhFactor { Negative, Positive };

/// @brief Struct of blood group data
struct BloodGroup {
 public:
  BloodGroup() = default;

  /// @brief Constructor
  /// @param blood_t Blood type
  /// @param rh_f Rh factor
  BloodGroup(BloodType blood_t, RhFactor rh_f)
      : blood_type_(blood_t), rh_factor_(rh_f) {}

  /**
   * @brief Checks if this blood group is compatible with
   * another
   * @param another The blood group to compare with
   * @return true if this blood group is compatible with another
   * @return false otherwise
   */
  bool operator>>(const BloodGroup& another);

 private:
  BloodType blood_type_;
  RhFactor rh_factor_;
};

/// @brief Enum of roles in an exchange program
enum struct Role { Donor, Recipient };

/// @brief Struct of exchange program data
struct Human : Vertex<std::size_t> {
 public:
  /// @brief Constructor
  Human(std::size_t id) : Vertex<std::size_t>(id) {}

  // Role of the person in the exchange program
  Role role;

  // Blood group of the person
  BloodGroup blood_group;

  std::set<std::shared_ptr<Human>> adjacent;
};

class BloodExchange
    : Graph<Human, std::size_t> {  // TODO: Write Bipartite graph class and
                                   // derive from it
 public:
  /// @brief Inizialized with sets of donors and recipients
  /// @param donors Set of donors
  /// @param recipients Set of recipients
  BloodExchange(std::vector<BloodGroup> donors,
                std::vector<BloodGroup> recipients) {
    for (std::size_t i = 0; i < donors.size(); ++i) {
      AddVertex(vertices_.size());
      vertices_[vertices_.size() - 1]->role = Role::Donor;
      vertices_[vertices_.size() - 1]->blood_group = donors[i];
    }

    for (std::size_t i = 0; i < recipients.size(); ++i) {
      AddVertex(vertices_.size());
      vertices_[vertices_.size() - 1]->role = Role::Recipient;
      vertices_[vertices_.size() - 1]->blood_group = recipients[i];
    }
  }

  /// @brief Finds maximal matching between donors and recipients
  /// @return std::size_t Maximal matching
  std::size_t FindMaxMatching();

 private:
  void AddVertex(const std::size_t& index) override {
    vertices_.push_back(std::make_shared<Human>(index));
  }

  bool MatchingUtil(std::size_t human_id, std::vector<bool>& matched,
                    std::vector<std::size_t>& matching);
};