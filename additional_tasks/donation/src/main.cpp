#include "utils.hpp"

int main() {
  // Example blood groups for donors and recipients
  std::vector<BloodGroup> donors = {
      BloodGroup(BloodType::O, RhFactor::Positive),
      BloodGroup(BloodType::A, RhFactor::Positive),
      BloodGroup(BloodType::B, RhFactor::Positive),
      BloodGroup(BloodType::AB, RhFactor::Positive),
      BloodGroup(BloodType::O, RhFactor::Negative),
      BloodGroup(BloodType::A, RhFactor::Negative)};

  std::vector<BloodGroup> recipients = {
      BloodGroup(BloodType::A, RhFactor::Positive),
      BloodGroup(BloodType::B, RhFactor::Positive),
      BloodGroup(BloodType::AB, RhFactor::Positive),
      BloodGroup(BloodType::O, RhFactor::Negative),
      BloodGroup(BloodType::O, RhFactor::Positive),
      BloodGroup(BloodType::AB, RhFactor::Negative)};

  BloodExchange bl_xchg(donors, recipients);

  std::cout << "Maximum number of donors that can match with recipients is "
            << bl_xchg.FindMaxMatching() << std::endl;

  return 0;
}