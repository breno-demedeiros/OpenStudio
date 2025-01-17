/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include "EnergyPlusFixture.hpp"

#include "../ForwardTranslator.hpp"

#include "../../model/Model.hpp"
#include "../../model/AvailabilityManagerHighTemperatureTurnOn.hpp"
#include "../../model/Node.hpp"
#include "../../model/PlantLoop.hpp"

#include <utilities/idd/AvailabilityManager_HighTemperatureTurnOn_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::energyplus;
using namespace openstudio::model;
using namespace openstudio;

TEST_F(EnergyPlusFixture, ForwardTranslator_AvailabilityManagerHighTemperatureTurnOn) {

  Model m;

  AvailabilityManagerHighTemperatureTurnOn avm(m);

  // Assign Sensor Node and Temperature
  Node n(m);
  EXPECT_TRUE(avm.setSensorNode(n));
  EXPECT_TRUE(avm.setTemperature(60.19));

  // Assign it to a plant loop
  PlantLoop p(m);
  p.addAvailabilityManager(avm);

  // ForwardTranslate
  ForwardTranslator forwardTranslator;
  Workspace workspace = forwardTranslator.translateModel(m);

  WorkspaceObjectVector idfObjs(workspace.getObjectsByType(IddObjectType::AvailabilityManager_HighTemperatureTurnOn));
  EXPECT_EQ(1u, idfObjs.size());
  WorkspaceObject idf_avm(idfObjs[0]);

  // Sensor Node Name
  ASSERT_EQ(n.name().get(), idf_avm.getString(AvailabilityManager_HighTemperatureTurnOnFields::SensorNodeName).get());

  // Temperature
  EXPECT_DOUBLE_EQ(avm.temperature(), idf_avm.getDouble(AvailabilityManager_HighTemperatureTurnOnFields::Temperature).get());
}

/*
 * The Forward Translator should throw if the AVM is missing the required Sensor Node (E+ crash on 8.8.0)
 */
TEST_F(EnergyPlusFixture, ForwardTranslator_AvailabilityManagerHighTemperatureTurnOn_NoSensorNode) {

  Model m;

  AvailabilityManagerHighTemperatureTurnOn avm(m);
  // No Sensor Node
  ASSERT_FALSE(avm.sensorNode());

  // Assign it to a plant loop (otherwise it's purely not translated anyways...)
  PlantLoop p(m);
  p.addAvailabilityManager(avm);

  // ForwardTranslate
  ForwardTranslator forwardTranslator;
  Workspace workspace = forwardTranslator.translateModel(m);

  EXPECT_EQ(1u, forwardTranslator.errors().size());
}
