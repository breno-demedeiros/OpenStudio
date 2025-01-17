/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "ModelFixture.hpp"

#include "../RefrigerationGasCoolerAirCooled.hpp"
#include "../RefrigerationGasCoolerAirCooled_Impl.hpp"
#include "../CurveLinear.hpp"
#include "../CurveLinear_Impl.hpp"
// #include <model/ThermalZone.hpp>
// #include <model/ThermalZone_Impl.hpp>

using namespace openstudio;
using namespace openstudio::model;

//Test construction of air-cooled gas cooler
TEST_F(ModelFixture, RefrigerationGasCoolerAirCooled_DefaultConstructor) {
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";

  ASSERT_EXIT(
    {
      Model model;
      RefrigerationGasCoolerAirCooled testObject = RefrigerationGasCoolerAirCooled(model);

      exit(0);
    },
    ::testing::ExitedWithCode(0), "");
}

//Test removal of air-cooled gas cooler
TEST_F(ModelFixture, RefrigerationGasCoolerAirCooled_Remove) {
  Model model;
  RefrigerationGasCoolerAirCooled testObject = RefrigerationGasCoolerAirCooled(model);

  std::vector<RefrigerationGasCoolerAirCooled> refrigerationAirCooledGasCoolers = model.getConcreteModelObjects<RefrigerationGasCoolerAirCooled>();
  EXPECT_EQ(1, refrigerationAirCooledGasCoolers.size());

  std::vector<CurveLinear> ratedTotalHeatRejectionRateCurve = model.getConcreteModelObjects<CurveLinear>();
  EXPECT_EQ(1, ratedTotalHeatRejectionRateCurve.size());

  testObject.remove();

  refrigerationAirCooledGasCoolers = model.getConcreteModelObjects<RefrigerationGasCoolerAirCooled>();
  EXPECT_EQ(0, refrigerationAirCooledGasCoolers.size());

  // Curve was used only by this object, so should have been removed
  ratedTotalHeatRejectionRateCurve = model.getConcreteModelObjects<CurveLinear>();
  EXPECT_EQ(0, ratedTotalHeatRejectionRateCurve.size());
}

//Test the methods that set and get the fields
TEST_F(ModelFixture, RefrigerationGasCoolerAirCooled_set_get) {
  Model model;

  RefrigerationGasCoolerAirCooled gascooler(model);

  gascooler.setGasCoolerFanSpeedControlType("Fixed");
  gascooler.setRatedFanPower(99.0);
  gascooler.setMinimumFanAirFlowRatio(0.9);
  gascooler.setTransitionTemperature(99.0);
  gascooler.setTranscriticalApproachTemperature(9.0);
  gascooler.setSubcriticalTemperatureDifference(9.0);
  gascooler.setMinimumCondensingTemperature(9.0);
  gascooler.setEndUseSubcategory("EndUseCat");
  gascooler.setGasCoolerRefrigerantOperatingChargeInventory(99.0);
  gascooler.setGasCoolerReceiverRefrigerantInventory(99.0);
  gascooler.setGasCoolerOutletPipingRefrigerantInventory(99.0);

  EXPECT_EQ(gascooler.gasCoolerFanSpeedControlType(), "Fixed");
  EXPECT_DOUBLE_EQ(gascooler.ratedFanPower(), 99.0);
  EXPECT_DOUBLE_EQ(gascooler.minimumFanAirFlowRatio(), 0.9);
  EXPECT_DOUBLE_EQ(gascooler.transitionTemperature(), 99.0);
  EXPECT_DOUBLE_EQ(gascooler.transcriticalApproachTemperature(), 9.0);
  EXPECT_DOUBLE_EQ(gascooler.subcriticalTemperatureDifference(), 9.0);
  EXPECT_DOUBLE_EQ(gascooler.minimumCondensingTemperature(), 9.0);
  EXPECT_EQ(gascooler.endUseSubcategory(), "EndUseCat");
  EXPECT_DOUBLE_EQ(gascooler.gasCoolerRefrigerantOperatingChargeInventory(), 99.0);
  EXPECT_DOUBLE_EQ(gascooler.gasCoolerReceiverRefrigerantInventory(), 99.0);
  EXPECT_DOUBLE_EQ(gascooler.gasCoolerOutletPipingRefrigerantInventory(), 99.0);
}

//Test clone model with default data
TEST_F(ModelFixture, RefrigerationGasCoolerAirCooled_CloneModelWithDefaultData) {
  Model model;

  RefrigerationGasCoolerAirCooled testObject = RefrigerationGasCoolerAirCooled(model);

  auto testObjectClone = testObject.clone(model).cast<RefrigerationGasCoolerAirCooled>();

  std::vector<CurveLinear> refrigerationGasCoolerCurves = model.getConcreteModelObjects<CurveLinear>();
  for (auto it = refrigerationGasCoolerCurves.begin(); it != refrigerationGasCoolerCurves.end(); ++it) {
    EXPECT_TRUE(it->parent());
  }

  EXPECT_EQ(testObjectClone.gasCoolerFanSpeedControlType(), "VariableSpeed");
  EXPECT_DOUBLE_EQ(testObjectClone.ratedFanPower(), 12000.0);
  EXPECT_DOUBLE_EQ(testObjectClone.minimumFanAirFlowRatio(), 0.2);
  EXPECT_DOUBLE_EQ(testObjectClone.transitionTemperature(), 27.0);
  EXPECT_DOUBLE_EQ(testObjectClone.transcriticalApproachTemperature(), 3.0);
  EXPECT_DOUBLE_EQ(testObjectClone.subcriticalTemperatureDifference(), 10.0);
  EXPECT_DOUBLE_EQ(testObjectClone.minimumCondensingTemperature(), 10.0);
  EXPECT_EQ(testObjectClone.endUseSubcategory(), "General");
  EXPECT_DOUBLE_EQ(testObjectClone.gasCoolerRefrigerantOperatingChargeInventory(), 0.0);
  EXPECT_DOUBLE_EQ(testObjectClone.gasCoolerReceiverRefrigerantInventory(), 0.0);
  EXPECT_DOUBLE_EQ(testObjectClone.gasCoolerOutletPipingRefrigerantInventory(), 0.0);
  EXPECT_EQ(testObject.ratedTotalHeatRejectionRateCurve().get().handle(), testObjectClone.ratedTotalHeatRejectionRateCurve().get().handle());
}

//Test clone model with custom data
TEST_F(ModelFixture, RefrigerationGasCoolerAirCooled_CloneModelWithCustomData) {
  Model model;
  // ThermalZone thermalZone(model);

  RefrigerationGasCoolerAirCooled testObject = RefrigerationGasCoolerAirCooled(model);

  testObject.setGasCoolerFanSpeedControlType("VariableSpeed");
  testObject.setRatedFanPower(99.0);
  testObject.setMinimumFanAirFlowRatio(0.9);
  testObject.setTransitionTemperature(99.0);
  testObject.setTranscriticalApproachTemperature(9.0);
  testObject.setSubcriticalTemperatureDifference(9.0);
  testObject.setMinimumCondensingTemperature(9.0);
  testObject.setEndUseSubcategory("EndUseCat");
  testObject.setGasCoolerRefrigerantOperatingChargeInventory(99.0);
  testObject.setGasCoolerReceiverRefrigerantInventory(99.0);
  testObject.setGasCoolerOutletPipingRefrigerantInventory(99.0);
  // testObject.setAirInletNode(thermalZone);

  auto testObjectClone = testObject.clone(model).cast<RefrigerationGasCoolerAirCooled>();

  EXPECT_EQ(testObjectClone.gasCoolerFanSpeedControlType(), "VariableSpeed");
  EXPECT_DOUBLE_EQ(testObjectClone.ratedFanPower(), 99.0);
  EXPECT_DOUBLE_EQ(testObjectClone.minimumFanAirFlowRatio(), 0.9);
  EXPECT_DOUBLE_EQ(testObjectClone.transitionTemperature(), 99.0);
  EXPECT_DOUBLE_EQ(testObjectClone.transcriticalApproachTemperature(), 9.0);
  EXPECT_DOUBLE_EQ(testObjectClone.subcriticalTemperatureDifference(), 9.0);
  EXPECT_DOUBLE_EQ(testObjectClone.minimumCondensingTemperature(), 9.0);
  EXPECT_EQ(testObjectClone.endUseSubcategory(), "EndUseCat");
  EXPECT_DOUBLE_EQ(testObjectClone.gasCoolerRefrigerantOperatingChargeInventory(), 99.0);
  EXPECT_DOUBLE_EQ(testObjectClone.gasCoolerReceiverRefrigerantInventory(), 99.0);
  EXPECT_DOUBLE_EQ(testObjectClone.gasCoolerOutletPipingRefrigerantInventory(), 99.0);
  // EXPECT_FALSE(testObjectClone.airInletNode());
}

//Test clone model with custom data
TEST_F(ModelFixture, RefrigerationGasCoolerAirCooled_CloneTwoModelWithCustomData) {
  Model model;
  // ThermalZone thermalZone(model);

  RefrigerationGasCoolerAirCooled testObject = RefrigerationGasCoolerAirCooled(model);

  testObject.setGasCoolerFanSpeedControlType("VariableSpeed");
  testObject.setRatedFanPower(99.0);
  testObject.setMinimumFanAirFlowRatio(0.9);
  testObject.setTransitionTemperature(99.0);
  testObject.setTranscriticalApproachTemperature(9.0);
  testObject.setSubcriticalTemperatureDifference(9.0);
  testObject.setMinimumCondensingTemperature(9.0);
  testObject.setEndUseSubcategory("EndUseCat");
  testObject.setGasCoolerRefrigerantOperatingChargeInventory(99.0);
  testObject.setGasCoolerReceiverRefrigerantInventory(99.0);
  testObject.setGasCoolerOutletPipingRefrigerantInventory(99.0);
  // testObject.setAirInletNode(thermalZone);

  auto testObjectClone = testObject.clone(model).cast<RefrigerationGasCoolerAirCooled>();

  Model model2;
  auto testObjectClone2 = testObject.clone(model2).cast<RefrigerationGasCoolerAirCooled>();

  EXPECT_EQ(testObjectClone2.gasCoolerFanSpeedControlType(), "VariableSpeed");
  EXPECT_DOUBLE_EQ(testObjectClone2.ratedFanPower(), 99.0);
  EXPECT_DOUBLE_EQ(testObjectClone2.minimumFanAirFlowRatio(), 0.9);
  EXPECT_DOUBLE_EQ(testObjectClone2.transitionTemperature(), 99.0);
  EXPECT_DOUBLE_EQ(testObjectClone2.transcriticalApproachTemperature(), 9.0);
  EXPECT_DOUBLE_EQ(testObjectClone2.subcriticalTemperatureDifference(), 9.0);
  EXPECT_DOUBLE_EQ(testObjectClone2.minimumCondensingTemperature(), 9.0);
  EXPECT_EQ(testObjectClone2.endUseSubcategory(), "EndUseCat");
  EXPECT_DOUBLE_EQ(testObjectClone2.gasCoolerRefrigerantOperatingChargeInventory(), 99.0);
  EXPECT_DOUBLE_EQ(testObjectClone2.gasCoolerReceiverRefrigerantInventory(), 99.0);
  EXPECT_DOUBLE_EQ(testObjectClone2.gasCoolerOutletPipingRefrigerantInventory(), 99.0);
  EXPECT_TRUE(testObjectClone2.ratedTotalHeatRejectionRateCurve());
  EXPECT_NE(testObjectClone2.ratedTotalHeatRejectionRateCurve().get(), testObject.ratedTotalHeatRejectionRateCurve().get());
  // EXPECT_FALSE(testObjectClone2.airInletNode());
  EXPECT_NE(testObjectClone2, testObjectClone);
  EXPECT_NE(testObjectClone, testObject);
}
