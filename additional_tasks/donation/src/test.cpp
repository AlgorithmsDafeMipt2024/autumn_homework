#include <gtest/gtest.h>

#include "utils.hpp"

TEST(Compatibility, ABO_Type) {
  BloodGroup donorA(BloodType::A, RhFactor::Negative);
  BloodGroup donorB(BloodType::B, RhFactor::Negative);

  BloodGroup recipientO(BloodType::O, RhFactor::Negative);
  BloodGroup recipientAB(BloodType::AB, RhFactor::Negative);

  EXPECT_TRUE(donorA >> recipientAB);  // A can donate to AB
  EXPECT_TRUE(donorB >> recipientAB);  // B can donate to AB
  EXPECT_FALSE(donorA >> recipientO);  // A cannot donate to O
  EXPECT_FALSE(donorB >> recipientO);  // B cannot donate to O
}

TEST(Compatibility, Rh_Factor) {
  BloodGroup donorO(BloodType::O, RhFactor::Positive);
  BloodGroup donorAB(BloodType::AB, RhFactor::Positive);

  BloodGroup recipientO(BloodType::O, RhFactor::Negative);
  BloodGroup recipientAB(BloodType::AB, RhFactor::Negative);

  EXPECT_FALSE(donorO >> recipientO);    // O+ cannot donate to O-
  EXPECT_FALSE(donorAB >> recipientAB);  // AB+ cannot donate to AB-
}

TEST(MaxMatching, NoMatches) {
  std::vector<BloodGroup> donors = {
      BloodGroup(BloodType::O, RhFactor::Positive),
      BloodGroup(BloodType::A, RhFactor::Positive),
      BloodGroup(BloodType::B, RhFactor::Positive),
      BloodGroup(BloodType::AB, RhFactor::Positive)};

  std::vector<BloodGroup> recipients = {
      BloodGroup(BloodType::A, RhFactor::Negative),
      BloodGroup(BloodType::B, RhFactor::Negative),
      BloodGroup(BloodType::AB, RhFactor::Negative),
      BloodGroup(BloodType::O, RhFactor::Negative)};

  BloodExchange bl_xchg(donors, recipients);
  EXPECT_EQ(bl_xchg.FindMaxMatching(), 0);
}

TEST(MaxMatching, MaxMatching) {
  std::vector<BloodGroup> donors = {
      BloodGroup(BloodType::O, RhFactor::Positive),
      BloodGroup(BloodType::A, RhFactor::Positive),
      BloodGroup(BloodType::B, RhFactor::Negative),
      BloodGroup(BloodType::AB, RhFactor::Positive)};

  std::vector<BloodGroup> recipients = {
      BloodGroup(BloodType::A, RhFactor::Positive),
      BloodGroup(BloodType::B, RhFactor::Negative),
      BloodGroup(BloodType::AB, RhFactor::Positive),
      BloodGroup(BloodType::O, RhFactor::Negative)};

  BloodExchange bl_xchg_mixed(donors, recipients);
  EXPECT_EQ(bl_xchg_mixed.FindMaxMatching(), 3);
}

TEST(Compatibility, MixedBloodTypes) {
  BloodGroup donorOPos(BloodType::O, RhFactor::Positive);
  BloodGroup donorONeg(BloodType::O, RhFactor::Negative);
  BloodGroup donorANeg(BloodType::A, RhFactor::Negative);
  BloodGroup donorBPos(BloodType::B, RhFactor::Positive);
  BloodGroup donorABPos(BloodType::AB, RhFactor::Positive);

  BloodGroup recipientOPos(BloodType::O, RhFactor::Positive);
  BloodGroup recipientANeg(BloodType::A, RhFactor::Negative);
  BloodGroup recipientBPos(BloodType::B, RhFactor::Positive);
  BloodGroup recipientABPos(BloodType::AB, RhFactor::Positive);
  BloodGroup recipientABNeg(BloodType::AB, RhFactor::Negative);

  EXPECT_TRUE(donorOPos >> recipientOPos);
  EXPECT_TRUE(donorONeg >> recipientOPos);
  EXPECT_FALSE(donorANeg >> recipientOPos);
  EXPECT_TRUE(donorBPos >> recipientBPos);
  EXPECT_TRUE(donorABPos >> recipientABPos);
  EXPECT_FALSE(donorABPos >> recipientABNeg);
}

TEST(Compatibility, EdgeCases) {
  BloodGroup donorOPos(BloodType::O, RhFactor::Positive);
  BloodGroup recipientOPos(BloodType::O, RhFactor::Positive);
  BloodGroup recipientOPosNeg(BloodType::O, RhFactor::Negative);
  BloodGroup recipientABNeg(BloodType::AB, RhFactor::Negative);

  EXPECT_TRUE(donorOPos >> recipientOPos);
  EXPECT_FALSE(donorOPos >> recipientOPosNeg);
  EXPECT_FALSE(donorOPos >> recipientABNeg);
}

TEST(MaxMatching, MultipleDonorsAndRecipients) {
  std::vector<BloodGroup> donors = {
      BloodGroup(BloodType::O, RhFactor::Positive),
      BloodGroup(BloodType::A, RhFactor::Positive),
      BloodGroup(BloodType::B, RhFactor::Negative),
      BloodGroup(BloodType::AB, RhFactor::Positive),
      BloodGroup(BloodType::O, RhFactor::Negative)};

  std::vector<BloodGroup> recipients = {
      BloodGroup(BloodType::A, RhFactor::Positive),
      BloodGroup(BloodType::B, RhFactor::Positive),
      BloodGroup(BloodType::AB, RhFactor::Positive),
      BloodGroup(BloodType::O, RhFactor::Negative),
      BloodGroup(BloodType::O, RhFactor::Positive),
      BloodGroup(BloodType::AB, RhFactor::Negative)};

  BloodExchange bl_xchg(donors, recipients);
  EXPECT_EQ(bl_xchg.FindMaxMatching(), 5);
}

TEST(MaxMatching, AllIncompatible) {
  std::vector<BloodGroup> donors = {
      BloodGroup(BloodType::A, RhFactor::Positive),
      BloodGroup(BloodType::B, RhFactor::Positive),
  };

  std::vector<BloodGroup> recipients = {
      BloodGroup(BloodType::O, RhFactor::Negative),
      BloodGroup(BloodType::AB, RhFactor::Negative),
  };

  BloodExchange bl_xchg(donors, recipients);
  EXPECT_EQ(bl_xchg.FindMaxMatching(), 0);  // No matches possible
}

TEST(MaxMatching, CompleteCompatibility) {
  std::vector<BloodGroup> donors = {
      BloodGroup(BloodType::O, RhFactor::Positive),
      BloodGroup(BloodType::O, RhFactor::Negative),
      BloodGroup(BloodType::A, RhFactor::Positive),
      BloodGroup(BloodType::A, RhFactor::Negative),
      BloodGroup(BloodType::B, RhFactor::Positive),
      BloodGroup(BloodType::B, RhFactor::Negative),
      BloodGroup(BloodType::AB, RhFactor ::Positive),
      BloodGroup(BloodType::AB, RhFactor::Negative)};

  std::vector<BloodGroup> recipients = {
      BloodGroup(BloodType::O, RhFactor::Positive),
      BloodGroup(BloodType::O, RhFactor::Negative),
      BloodGroup(BloodType::A, RhFactor::Positive),
      BloodGroup(BloodType::A, RhFactor::Negative),
      BloodGroup(BloodType::B, RhFactor::Positive),
      BloodGroup(BloodType::B, RhFactor::Negative),
      BloodGroup(BloodType::AB, RhFactor::Positive),
      BloodGroup(BloodType::AB, RhFactor::Negative)};

  BloodExchange bl_xchg(donors, recipients);
  EXPECT_EQ(bl_xchg.FindMaxMatching(),
            8);  // All donors can match with all recipients
}
