/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "../ForwardTranslator.hpp"
#include "../../model/Schedule.hpp"
#include "../../model/Schedule_Impl.hpp"
#include "../../model/ThermalZone.hpp"
#include "../../model/ThermalZone_Impl.hpp"
#include "../../model/ZoneControlThermostatStagedDualSetpoint.hpp"
#include "../../model/ZoneControlThermostatStagedDualSetpoint_Impl.hpp"
#include "../../utilities/idf/IdfExtensibleGroup.hpp"
#include <utilities/idd/ZoneControl_Thermostat_StagedDualSetpoint_FieldEnums.hxx>
#include <utilities/idd/ThermostatSetpoint_DualSetpoint_FieldEnums.hxx>
#include <utilities/idd/ZoneControl_Thermostat_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::model;

using namespace std;

namespace openstudio {

namespace energyplus {

  boost::optional<IdfObject>
    ForwardTranslator::translateZoneControlThermostatStagedDualSetpoint(ZoneControlThermostatStagedDualSetpoint& modelObject) {
    boost::optional<std::string> s;
    boost::optional<double> value;
    int num;

    IdfObject idfObject(openstudio::IddObjectType::ZoneControl_Thermostat_StagedDualSetpoint);

    m_idfObjects.push_back(idfObject);

    s = modelObject.name();
    idfObject.setName(s.get());

    boost::optional<IdfObject> _zone;
    // ZoneorZoneListName
    if (auto zone = modelObject.thermalZone()) {
      if ((_zone = translateAndMapModelObject(zone.get()))) {
        idfObject.setString(ZoneControl_Thermostat_StagedDualSetpointFields::ZoneorZoneListName, _zone->name().get());
      }
    }

    // NumberofHeatingStages
    num = modelObject.numberofHeatingStages();
    idfObject.setInt(ZoneControl_Thermostat_StagedDualSetpointFields::NumberofHeatingStages, num);

    // HeatingTemperatureSetpointScheduleName
    boost::optional<IdfObject> _heatingSchedule;
    if (auto heatingSchedule = modelObject.heatingTemperatureSetpointSchedule()) {
      if ((_heatingSchedule = translateAndMapModelObject(heatingSchedule.get()))) {
        idfObject.setString(ZoneControl_Thermostat_StagedDualSetpointFields::HeatingTemperatureSetpointScheduleName, _heatingSchedule->name().get());
      }
    }

    // HeatingThrottlingTemperatureRange
    if ((value = modelObject.heatingThrottlingTemperatureRange())) {
      idfObject.setDouble(ZoneControl_Thermostat_StagedDualSetpointFields::HeatingThrottlingTemperatureRange, value.get());
    }

    // Stage1HeatingTemperatureOffset
    if ((value = modelObject.stage1HeatingTemperatureOffset())) {
      idfObject.setDouble(ZoneControl_Thermostat_StagedDualSetpointFields::Stage1HeatingTemperatureOffset, value.get());
    }

    // Stage2HeatingTemperatureOffset
    if ((value = modelObject.stage2HeatingTemperatureOffset())) {
      idfObject.setDouble(ZoneControl_Thermostat_StagedDualSetpointFields::Stage2HeatingTemperatureOffset, value.get());
    }

    // Stage3HeatingTemperatureOffset
    if ((value = modelObject.stage3HeatingTemperatureOffset())) {
      idfObject.setDouble(ZoneControl_Thermostat_StagedDualSetpointFields::Stage3HeatingTemperatureOffset, value.get());
    }

    // Stage4HeatingTemperatureOffset
    if ((value = modelObject.stage4HeatingTemperatureOffset())) {
      idfObject.setDouble(ZoneControl_Thermostat_StagedDualSetpointFields::Stage4HeatingTemperatureOffset, value.get());
    }

    // NumberofCoolingStages
    num = modelObject.numberofCoolingStages();
    idfObject.setInt(ZoneControl_Thermostat_StagedDualSetpointFields::NumberofCoolingStages, num);

    // CoolingTemperatureSetpointBaseScheduleName
    boost::optional<IdfObject> _coolingSchedule;
    if (auto coolingSchedule = modelObject.coolingTemperatureSetpointBaseSchedule()) {
      if ((_coolingSchedule = translateAndMapModelObject(coolingSchedule.get()))) {
        idfObject.setString(ZoneControl_Thermostat_StagedDualSetpointFields::CoolingTemperatureSetpointBaseScheduleName,
                            _coolingSchedule->name().get());
      }
    }

    // CoolingThrottlingTemperatureRange
    if ((value = modelObject.coolingThrottlingTemperatureRange())) {
      idfObject.setDouble(ZoneControl_Thermostat_StagedDualSetpointFields::CoolingThrottlingTemperatureRange, value.get());
    }

    // Stage1CoolingTemperatureOffset
    if ((value = modelObject.stage1CoolingTemperatureOffset())) {
      idfObject.setDouble(ZoneControl_Thermostat_StagedDualSetpointFields::Stage1CoolingTemperatureOffset, value.get());
    }

    // Stage2CoolingTemperatureOffset
    if ((value = modelObject.stage2CoolingTemperatureOffset())) {
      idfObject.setDouble(ZoneControl_Thermostat_StagedDualSetpointFields::Stage2CoolingTemperatureOffset, value.get());
    }

    // Stage3CoolingTemperatureOffset
    if ((value = modelObject.stage3CoolingTemperatureOffset())) {
      idfObject.setDouble(ZoneControl_Thermostat_StagedDualSetpointFields::Stage3CoolingTemperatureOffset, value.get());
    }

    // Stage4CoolingTemperatureOffset
    if ((value = modelObject.stage4CoolingTemperatureOffset())) {
      idfObject.setDouble(ZoneControl_Thermostat_StagedDualSetpointFields::Stage4CoolingTemperatureOffset, value.get());
    }

    // TODO: this is probably not needed anymore
    // This is a workaround for EnergyPlus 8.1 bug
    if (_zone && _heatingSchedule && _coolingSchedule) {
      std::string baseName = _zone->name().get();

      IdfObject zoneControlThermostat(openstudio::IddObjectType::ZoneControl_Thermostat);
      zoneControlThermostat.setString(ZoneControl_ThermostatFields::Name, baseName + " AutoGenerated ZoneControl");
      zoneControlThermostat.setString(ZoneControl_ThermostatFields::ZoneorZoneListName, _zone->name().get());
      m_idfObjects.push_back(zoneControlThermostat);

      IdfObject scheduleCompact(openstudio::IddObjectType::Schedule_Compact);
      scheduleCompact.setName(baseName + " AutoGenerated Thermostat Type Schedule");
      m_idfObjects.push_back(scheduleCompact);
      scheduleCompact.setString(1, baseName + " AutoGenerated Thermostat Type Limits");
      scheduleCompact.setString(2, "Through: 12/31");
      scheduleCompact.setString(3, "For: AllDays");
      scheduleCompact.setString(4, "Until: 24:00");
      scheduleCompact.setString(5, "4");

      IdfObject scheduleTypeLimits(openstudio::IddObjectType::ScheduleTypeLimits);
      scheduleTypeLimits.setName(baseName + " AutoGenerated Thermostat Type Limits");
      m_idfObjects.push_back(scheduleTypeLimits);
      scheduleTypeLimits.setString(1, "0");
      scheduleTypeLimits.setString(2, "4");
      scheduleTypeLimits.setString(3, "DISCRETE");
      zoneControlThermostat.setString(ZoneControl_ThermostatFields::ControlTypeScheduleName, scheduleCompact.name().get());

      IdfObject idfThermostat(openstudio::IddObjectType::ThermostatSetpoint_DualSetpoint);
      m_idfObjects.push_back(idfThermostat);
      idfThermostat.setName(baseName + " AutoGenerated Thermostat");
      idfThermostat.setString(ThermostatSetpoint_DualSetpointFields::HeatingSetpointTemperatureScheduleName, _heatingSchedule->name().get());
      idfThermostat.setString(ThermostatSetpoint_DualSetpointFields::CoolingSetpointTemperatureScheduleName, _coolingSchedule->name().get());

      // TODO: JM 2019-09-04 switch back to an extensible object once/if https://github.com/NREL/EnergyPlus/issues/7484 is addressed and the
      // 'Temperature Difference Between Cutout And Setpoint' field is moved before the extensible fields
      // For now, we revert to a non extensible object, so we can still write that field
      //StringVector values(zoneControlThermostat.iddObject().properties().numExtensible);
      //values[ZoneControl_ThermostatExtensibleFields::ControlObjectType] = idfThermostat.iddObject().name();
      //values[ZoneControl_ThermostatExtensibleFields::ControlName] = idfThermostat.name().get();
      //IdfExtensibleGroup eg = zoneControlThermostat.pushExtensibleGroup(values);

      zoneControlThermostat.setString(ZoneControl_ThermostatFields::Control1ObjectType, idfThermostat.iddObject().name());
      zoneControlThermostat.setString(ZoneControl_ThermostatFields::Control1Name, idfThermostat.name().get());
    }

    return boost::optional<IdfObject>(idfObject);
  }

}  // namespace energyplus

}  // namespace openstudio
