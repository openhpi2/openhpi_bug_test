/*      -*- linux-c -*-
 *
 * (C) Copyright IBM Corp. 2003, 2004
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  This
 * file and program are licensed under a BSD style license.  See
 * the Copying file included with the OpenHPI distribution for
 * full licensing terms.
 *
 * Author(s):
 *      Sean Dague <http://dague.net/sean>
 *      Renier Morales <renierm@users.sf.net>
 *      Steve Sherman <stevees@us.ibm.com>
 */

/**************************************************************************
 * This source file defines the resource arrays declared in bc_resources.h
 *************************************************************************/

#include <SaHpi.h>
#include <bc_resources.h>

/*************************************************************************
 * RESTRICTIONS!!!
 *
 * - If IsThreshold=SAHPI_TRUE for an interpreted sensor,
 *   Range.Max.Interpreted.Type must be defined for snmp_bc.c
 *   get_interpreted_thresholds to work.
 * - Digital controls must be integers and depend on SaHpiStateDigitalT
 *************************************************************************/

/*************************************************************************
 *                   Resource Definitions
 *************************************************************************/
struct snmp_rpt snmp_rpt_array[] = {
        /* Chassis */
        {
                .rpt = {
                        .ResourceInfo = {
                                .ManufacturerId = IBM_MANUFACTURING_ID,
                        },
                        .ResourceEntity = {
                                .Entry[0] =
                                {
                                        .EntityType = SAHPI_ENT_ROOT,
                                        .EntityInstance = 0
                                }
                        },
                        .ResourceCapabilities = SAHPI_CAPABILITY_CONTROL |
                                                SAHPI_CAPABILITY_EVT_DEASSERTS |
                                                SAHPI_CAPABILITY_INVENTORY_DATA |
                                                SAHPI_CAPABILITY_RDR |
                                                SAHPI_CAPABILITY_RESOURCE |
                                                SAHPI_CAPABILITY_SEL |
                                                SAHPI_CAPABILITY_SENSOR,
                        .ResourceSeverity = SAHPI_CRITICAL,
                },
                .bc_res_info = {
                        .mib = {
                                .OidHealth = ".1.3.6.1.4.1.2.3.51.2.2.7.1.0",
                                .HealthyValue = 255,
                                .OidReset = '\0',
                                .OidPowerState = '\0',
                                .OidPowerOnOff = '\0',
                        },
                        .event_array = {
                                {},
                        },
                },
                .comment = "Top-level blade chassis"
        },
        /* Management module */
        {
                .rpt = {
                        .ResourceInfo = {
                                .ManufacturerId = IBM_MANUFACTURING_ID,
                        },
                        .ResourceEntity = {
                                .Entry[0] =
                                {
                                        .EntityType = SAHPI_ENT_SYS_MGMNT_MODULE,
                                        .EntityInstance = BC_HPI_INSTANCE_BASE
                                },
                                {
                                        .EntityType = SAHPI_ENT_ROOT,
                                        .EntityInstance = 0
                                }
                        },
                        .ResourceCapabilities = SAHPI_CAPABILITY_EVT_DEASSERTS |
                                                SAHPI_CAPABILITY_FRU |
                                                SAHPI_CAPABILITY_INVENTORY_DATA |
                                                SAHPI_CAPABILITY_RDR |
                                                SAHPI_CAPABILITY_RESOURCE,
                        .ResourceSeverity = SAHPI_MAJOR,
                },
                .bc_res_info = {
                        .mib = {
                                .OidHealth = '\0',
                                .HealthyValue = 0,
                                .OidReset = ".1.3.6.1.4.1.2.3.51.2.7.4.0",
                                .OidPowerState = '\0',
                                .OidPowerOnOff = '\0',
                        },
                        .event_array = {
                                {
                                        .event = "0028200x", /* EN_MM_x_INSTALLED */
                                        .event_state = SAHPI_HS_STATE_ACTIVE_HEALTHY,
                                        .recovery_state = SAHPI_HS_STATE_NOT_PRESENT,
                                },
                                {
                                        .event = "0028400x", /* EN_MM_x_REMOVED */
                                        .event_state = SAHPI_HS_STATE_NOT_PRESENT,
                                        .recovery_state = SAHPI_HS_STATE_ACTIVE_HEALTHY,
                                },
                                {},
                        },
                },
                .comment = "Management module"
        },
        /* Switch module */
        {
                .rpt = {
                        .ResourceInfo = {
                                .ManufacturerId = IBM_MANUFACTURING_ID,
                        },
                        .ResourceEntity = {
                                .Entry[0] =
                                {
                                        .EntityType = SAHPI_ENT_INTERCONNECT,
                                        .EntityInstance = BC_HPI_INSTANCE_BASE
                                },
                                {
                                        .EntityType = SAHPI_ENT_ROOT,
                                        .EntityInstance = 0
                                }
                        },
                        .ResourceCapabilities = SAHPI_CAPABILITY_FRU |
                                                SAHPI_CAPABILITY_INVENTORY_DATA |
                                                SAHPI_CAPABILITY_RDR |
                                                SAHPI_CAPABILITY_RESOURCE |
                                                SAHPI_CAPABILITY_SENSOR,
                        .ResourceSeverity = SAHPI_MAJOR,
                },
                .bc_res_info = {
                        .mib = {
                                .OidHealth = '\0',
                                .HealthyValue = 0,
                                .OidReset = ".1.3.6.1.4.1.2.3.51.2.22.3.1.1.1.8.x",
                                .OidPowerState = ".1.3.6.1.4.1.2.3.51.2.22.3.1.1.1.7.x",
                                .OidPowerOnOff = ".1.3.6.1.4.1.2.3.51.2.22.3.1.1.1.7.x",
                        },
                        .event_array = {
                                {
                                        .event = "0EA0200x", /* EN_SWITCH_x_INSTALLED */
                                        .event_state = SAHPI_HS_STATE_ACTIVE_HEALTHY,
                                        .recovery_state = SAHPI_HS_STATE_NOT_PRESENT,
                                },
                                {
                                        .event = "0EA0400x", /* EN_SWITCH_x_REMOVED */
                                        .event_state = SAHPI_HS_STATE_NOT_PRESENT,
                                        .recovery_state = SAHPI_HS_STATE_ACTIVE_HEALTHY,
                                },
                                {
                                        .event = "0EA0600x", /* EN_SWITCH_x_POWERED_OFF */
                                        .event_state = SAHPI_HS_STATE_NOT_PRESENT,
                                        .recovery_state = SAHPI_HS_STATE_ACTIVE_HEALTHY,
                                },
                                {
                                        .event = "0EA0800x", /* EN_SWITCH_x_POWERED_ON */
                                        .event_state = SAHPI_HS_STATE_ACTIVE_HEALTHY,
                                        .recovery_state = SAHPI_HS_STATE_NOT_PRESENT,
                                },
                                {
                                        .event = "0EA0000x", /* EN_FAULT_SWITCH_x */
                                        .event_state = SAHPI_HS_STATE_ACTIVE_UNHEALTHY,
                                        .recovery_state = SAHPI_HS_STATE_ACTIVE_HEALTHY,
                                },
                                {},
                        },
                },
                .comment = "Network switch module"
        },
        /* Blade */
        {
                .rpt = {
                        .ResourceInfo = {
                                .ManufacturerId = IBM_MANUFACTURING_ID,
                        },
                        .ResourceEntity = {
                                .Entry[0] =
                                {
                                        .EntityType = SAHPI_ENT_SBC_BLADE,
                                        .EntityInstance = BC_HPI_INSTANCE_BASE
                                },
                                {
                                        .EntityType = SAHPI_ENT_ROOT,
                                        .EntityInstance = 0
                                }
                        },
                        .ResourceCapabilities = SAHPI_CAPABILITY_CONTROL |
                                                SAHPI_CAPABILITY_EVT_DEASSERTS |
                                                SAHPI_CAPABILITY_FRU |
                                                SAHPI_CAPABILITY_INVENTORY_DATA |
                                                SAHPI_CAPABILITY_RDR |
                                                SAHPI_CAPABILITY_RESOURCE |
                                                SAHPI_CAPABILITY_SENSOR,
                        .ResourceSeverity = SAHPI_MAJOR,
                },
                .bc_res_info = {
                        .mib = {
                                .OidHealth = ".1.3.6.1.4.1.2.3.51.2.22.1.5.1.1.5.x",
                                .HealthyValue = 1,
                                .OidReset = ".1.3.6.1.4.1.2.3.51.2.22.1.6.1.1.8.x",
                                .OidPowerState = ".1.3.6.1.4.1.2.3.51.2.22.1.6.1.1.4.x",
                                .OidPowerOnOff = ".1.3.6.1.4.1.2.3.51.2.22.1.6.1.1.7.x",
                        },
                        .event_array = {
                                {
                                        .event = "0E00200x", /* EN_BLADE_x_INSTALLED */
                                        .event_state = SAHPI_HS_STATE_ACTIVE_HEALTHY,
                                        .recovery_state = SAHPI_HS_STATE_NOT_PRESENT,
                                },
                                {
                                        .event = "0E00400x", /* EN_BLADE_x_REMOVED */
                                        .event_state = SAHPI_HS_STATE_NOT_PRESENT,
                                        .recovery_state = SAHPI_HS_STATE_ACTIVE_HEALTHY,
                                },
                                {
                                        .event = "1C000001", /* EN_BLADE_PWR_DWN */
                                        .event_state = SAHPI_HS_STATE_NOT_PRESENT,
                                        .recovery_state = SAHPI_HS_STATE_ACTIVE_HEALTHY,
                                },
                                {
                                        .event = "1C000002",/* EN_BLADE_PWR_UP */
                                        .event_state = SAHPI_HS_STATE_ACTIVE_HEALTHY,
                                        .recovery_state = SAHPI_HS_STATE_NOT_PRESENT,
                                },
                                {
                                        .event = "06026080", /* EN_BLADE_PWR_DN_FAN_FAIL */
                                        .event_state = SAHPI_HS_STATE_NOT_PRESENT,
                                        .recovery_state = SAHPI_HS_STATE_ACTIVE_HEALTHY,
                                },
                                {
                                        .event = "0821C080", /* EN_BLADE_PWR_DN_PM_TEMP */
                                        .event_state = SAHPI_HS_STATE_NOT_PRESENT,
                                        .recovery_state = SAHPI_HS_STATE_ACTIVE_HEALTHY,
                                },
                                {},
                        },
                },
                .comment = "Blade"
        },
        /* Blade expansion (add-in) card */
        {
                .rpt = {
                        .ResourceInfo = {
                                .ManufacturerId = IBM_MANUFACTURING_ID,
                        },
                        .ResourceEntity = {
                                .Entry[0] =
                                {
                                        .EntityType = SAHPI_ENT_ADD_IN_CARD,
                                        .EntityInstance = BC_HPI_INSTANCE_BASE
                                },
                                {
                                        .EntityType = SAHPI_ENT_SBC_BLADE,
                                        .EntityInstance = BC_HPI_INSTANCE_BASE
                                },
                                {
                                        .EntityType = SAHPI_ENT_ROOT,
                                        .EntityInstance = 0
                                }
                        },
                        .ResourceCapabilities = SAHPI_CAPABILITY_EVT_DEASSERTS |
                                                SAHPI_CAPABILITY_RDR |
                                                SAHPI_CAPABILITY_RESOURCE |
			                        SAHPI_CAPABILITY_SENSOR,
                        .ResourceSeverity = SAHPI_MAJOR,
                },
                .bc_res_info = {
                        .mib = {
                                .OidHealth = '\0',
                                .HealthyValue = 0,
                                .OidReset = '\0',
                                .OidPowerState = '\0',
                                .OidPowerOnOff = '\0',
                        },
                        .event_array = {
                                {},
                        },
                },
                .comment = "Blade expansion card"
        },
        /* Media Tray */
        {
                .rpt = {
                        .ResourceInfo = {
                                .ManufacturerId = IBM_MANUFACTURING_ID,
                        },
                        .ResourceEntity = {
                                .Entry[0] =
                                {
                                        .EntityType = SAHPI_ENT_PERIPHERAL_BAY,
                                        .EntityInstance = BC_HPI_INSTANCE_BASE
                                },
                                {
                                        .EntityType = SAHPI_ENT_ROOT,
                                        .EntityInstance = 0
                                }
                        },
                        .ResourceCapabilities = SAHPI_CAPABILITY_INVENTORY_DATA |
                                                SAHPI_CAPABILITY_RDR |
                                                SAHPI_CAPABILITY_RESOURCE |
                                                SAHPI_CAPABILITY_SENSOR,
                        .ResourceSeverity = SAHPI_MAJOR,
                },
                .bc_res_info = {
                        .mib = {
                                .OidHealth = '\0',
                                .HealthyValue = 0,
                                .OidReset = '\0',
                                .OidPowerState = '\0',
                                .OidPowerOnOff = '\0',
                        },
                        .event_array = {
                                {
                                        .event = "06A1E001", /* EN_MEDIA_TRAY_REMOVED */
                                        .event_state = SAHPI_HS_STATE_NOT_PRESENT,
                                        .recovery_state = SAHPI_HS_STATE_ACTIVE_HEALTHY,
                                },
                                {
                                        .event = "09020000", /* EN_FAULT_FP_R */
                                        .event_state = SAHPI_HS_STATE_ACTIVE_UNHEALTHY,
                                        .recovery_state = SAHPI_HS_STATE_ACTIVE_HEALTHY,
                                },
                                {},
                        },
                },
                .comment = "Control panel/Media tray"
        },
        /* Blower module */
        {
                .rpt = {
                        .ResourceInfo = {
                                .ManufacturerId = IBM_MANUFACTURING_ID,
                        },
                        .ResourceEntity = {
                                .Entry[0] =
                                {
                                        .EntityType = SAHPI_ENT_FAN,
                                        .EntityInstance = BC_HPI_INSTANCE_BASE
                                },
                                {
                                        .EntityType = SAHPI_ENT_ROOT,
                                        .EntityInstance = 0
                                }
                        },
                        .ResourceCapabilities = SAHPI_CAPABILITY_EVT_DEASSERTS |
                                                SAHPI_CAPABILITY_FRU |
                                                SAHPI_CAPABILITY_RESOURCE |
                                                SAHPI_CAPABILITY_RDR |
                                                SAHPI_CAPABILITY_SENSOR,
                        .ResourceSeverity = SAHPI_MAJOR,
                 },
                .bc_res_info = {
                        .mib = {
                                .OidHealth = '\0',
                                .HealthyValue = 0,
                                .OidReset = '\0',
                                .OidPowerState = '\0',
                                .OidPowerOnOff = '\0',
                        },
                        .event_array = {
                                {},
                        },
                },
                .comment = "Blower module"
        },
        /* Power module */
        {
                .rpt = {
                        .ResourceInfo = {
                                .ManufacturerId = IBM_MANUFACTURING_ID,
                        },
                        .ResourceEntity = {
                                .Entry[0] =
                                {
                                        .EntityType = SAHPI_ENT_POWER_SUPPLY,
                                        .EntityInstance = BC_HPI_INSTANCE_BASE
                                },
                                {
                                        .EntityType = SAHPI_ENT_ROOT,
                                        .EntityInstance = 0
                                }
                        },
                        .ResourceCapabilities = SAHPI_CAPABILITY_FRU |
                                                SAHPI_CAPABILITY_INVENTORY_DATA |
                                                SAHPI_CAPABILITY_RESOURCE |
                                                SAHPI_CAPABILITY_RDR |
                                                SAHPI_CAPABILITY_SENSOR,
                        .ResourceSeverity = SAHPI_MAJOR,
                 },
                .bc_res_info = {
                        .mib = {
                                .OidHealth = '\0',
                                .HealthyValue = 0,
                                .OidReset = '\0',
                                .OidPowerState = '\0',
                                .OidPowerOnOff = '\0',
                        },
                        .event_array = {
                                {
                                        .event = "0821600x", /* EN_PSx_INSTALLED */
                                        .event_state = SAHPI_HS_STATE_ACTIVE_HEALTHY,
                                        .recovery_state = SAHPI_HS_STATE_NOT_PRESENT,
                                },
                                {
                                        .event = "0821E00x", /* EN_PSx_REMOVED */
                                        .event_state = SAHPI_HS_STATE_NOT_PRESENT,
                                        .recovery_state = SAHPI_HS_STATE_ACTIVE_HEALTHY,
                                },
                                {},
                        },
                },
                .comment = "Power module"
        },

        {} /* Terminate array with a null element */
};

/******************************************************************************
 *                      Sensor Definitions
 ******************************************************************************/

/*****************
 * Chassis Sensors
 *****************/

struct snmp_bc_sensor snmp_bc_chassis_sensors[] = {

        /* System Error LED on chassis */
        {
                .sensor = {
                        .Num = 1,
                        .Type = SAHPI_PLATFORM_VIOLATION,
                        .Category = SAHPI_EC_SEVERITY,
                        .EventCtrl = SAHPI_SEC_NO_EVENTS,
                        .Events = SAHPI_ES_OK | SAHPI_ES_CRITICAL,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_EVENT_STATE | SAHPI_SRF_RAW,
                                .IsNumeric = SAHPI_TRUE,
                                .SignFormat = SAHPI_SDF_UNSIGNED,
                                .BaseUnits = SAHPI_SU_UNSPECIFIED,
                                .ModifierUnits = SAHPI_SU_UNSPECIFIED,
                                .ModifierUse = SAHPI_SMUU_NONE,
                                .FactorsStatic = SAHPI_TRUE,
                                .Factors = {
                                        .M_Factor = 1,
                                        .Linearization = SAHPI_SL_NONLINEAR,
                                },
                                .Percentage = SAHPI_FALSE,
                                .Range = {
                                        .Flags = SAHPI_SRF_MIN | SAHPI_SRF_MAX,
                                        .Max = {
                                                .ValuesPresent = SAHPI_SRF_EVENT_STATE | SAHPI_SRF_RAW,
                                                .Raw = 1,
                                                .EventStatus = {
                                                        .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                                        .EventStatus = SAHPI_ES_CRITICAL,
                                                }
                                        },
                                        .Min = {
                                                .ValuesPresent = SAHPI_SRF_EVENT_STATE | SAHPI_SRF_RAW,
                                                .Raw = 0,
                                                .EventStatus = {
                                                        .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                                        .EventStatus = SAHPI_ES_OK,
                                                }
                                        }
                                }
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_FALSE
                        },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_OK,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_OK | SAHPI_ES_CRITICAL,
                                .DeassertEvents = SAHPI_ES_OK | SAHPI_ES_CRITICAL,
                        },
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .convert_snmpstr = -1,
                                .oid = ".1.3.6.1.4.1.2.3.51.2.2.8.1.1.0",
                        },
                        .event_array = {
                                {},
                        },
                },
                .comment = "Front Panel LED - System Error"
        },
        /* Temperature LED on the chassis */
        {
                .sensor = {
                        .Num = 2,
                        .Type = SAHPI_TEMPERATURE,
                        .Category = SAHPI_EC_SEVERITY,
                        .EventCtrl = SAHPI_SEC_NO_EVENTS,
                        .Events = SAHPI_ES_OK | SAHPI_ES_CRITICAL,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_EVENT_STATE | SAHPI_SRF_RAW,
                                .IsNumeric = SAHPI_TRUE,
                                .SignFormat = SAHPI_SDF_UNSIGNED,
                                .BaseUnits = SAHPI_SU_UNSPECIFIED,
                                .ModifierUnits = SAHPI_SU_UNSPECIFIED,
                                .ModifierUse = SAHPI_SMUU_NONE,
                                .FactorsStatic = SAHPI_TRUE,
                                .Factors = {
                                        .M_Factor = 1,
                                        .Linearization = SAHPI_SL_NONLINEAR,
                                },
                                .Percentage = SAHPI_FALSE,
                                .Range = {
                                        .Flags = SAHPI_SRF_MIN | SAHPI_SRF_MAX,
                                        .Max = {
                                                .ValuesPresent = SAHPI_SRF_EVENT_STATE | SAHPI_SRF_RAW,
                                                .Raw = 1,
                                                .EventStatus = {
                                                        .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                                        .EventStatus = SAHPI_ES_CRITICAL
                                                }
                                        },
                                        .Min = {
                                                .ValuesPresent = SAHPI_SRF_EVENT_STATE | SAHPI_SRF_RAW,
                                                .Raw = 0,
                                                .EventStatus = {
                                                        .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                                        .EventStatus = SAHPI_ES_OK
                                                }
                                        }
                                }
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_FALSE
                        },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_OK,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_OK | SAHPI_ES_CRITICAL,
                                .DeassertEvents = SAHPI_ES_OK | SAHPI_ES_CRITICAL,
                        },
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .convert_snmpstr = -1,
                                .oid = ".1.3.6.1.4.1.2.3.51.2.2.8.1.3.0",
                        },
                        .event_array = {
                                {},
                        },
                },
                 .comment = "Front Panel LED - Temperature"
        },
        /* Ambient air thermal sensor on Control Panel/Media Tray */
        {
                .sensor = {
                        .Num = 3,
                        .Type = SAHPI_TEMPERATURE,
                        .Category = SAHPI_EC_THRESHOLD,
                        .EventCtrl = SAHPI_SEC_GLOBAL_DISABLE,
                        .Events = SAHPI_ES_UNSPECIFIED | SAHPI_ES_UPPER_MINOR |
                                  SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_INTERPRETED,
                                .IsNumeric = SAHPI_TRUE,
                                .SignFormat = SAHPI_SDF_UNSIGNED,
                                .BaseUnits = SAHPI_SU_DEGREES_C,
                                .ModifierUnits = SAHPI_SU_UNSPECIFIED,
                                .ModifierUse = SAHPI_SMUU_NONE,
                                .FactorsStatic = SAHPI_TRUE,
                                .Factors = {
                                        .Linearization = SAHPI_SL_LINEAR,
                                },
                                .Percentage = SAHPI_FALSE,
                                .Range = {
                                        .Flags = SAHPI_SRF_MAX | SAHPI_SRF_MIN,
                                        .Max = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 125,
                                                        }
                                                },
                                        },
                                        .Min = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 0,
                                                        }
                                                },
                                        },
                                },
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_TRUE,
                                .TholdCapabilities = SAHPI_STC_INTERPRETED,
                                .ReadThold = 0, /* No Readable thresholds */
                                /* Default HDW thresholds: Warning=60; Warning Reset=55 */
                        },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_UNSPECIFIED,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                                .DeassertEvents = SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        },
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .convert_snmpstr = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                .oid = ".1.3.6.1.4.1.2.3.51.2.2.1.5.1.0",
                        },
                        .event_array = {
                                {
                                        .event = "0001C480", /* EN_CUTOFF_HI_OVER_TEMP_AMBIENT */
                                        .event_state = SAHPI_ES_UPPER_CRIT | SAHPI_ES_UPPER_MAJOR |
                                                          SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                },
                                {
                                        .event = "0001D500", /* EN_PFA_HI_OVER_TEMP_AMBIENT */
                                        .event_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UNSPECIFIED,
                                },
                                {},
                        },
                },
                .comment = "Ambient temperature sensor"
        },
        /* Thermal sensor on Management Module */
        {
                .sensor = {
                        .Num = 4,
                        .Type = SAHPI_TEMPERATURE,
                        .Category = SAHPI_EC_THRESHOLD,
                        .EventCtrl = SAHPI_SEC_GLOBAL_DISABLE,
                        .Events = SAHPI_ES_UNSPECIFIED | SAHPI_ES_UPPER_MINOR |
                                  SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_INTERPRETED,
                                .IsNumeric = SAHPI_TRUE,
                                .SignFormat = SAHPI_SDF_UNSIGNED,
                                .BaseUnits = SAHPI_SU_DEGREES_C,
                                .ModifierUnits = SAHPI_SU_UNSPECIFIED,
                                .ModifierUse = SAHPI_SMUU_NONE,
                                .FactorsStatic = SAHPI_TRUE,
                                .Factors = {
                                        .Linearization = SAHPI_SL_LINEAR,
                                },
                                .Percentage = SAHPI_FALSE,
                                .Range = {
                                        .Flags = SAHPI_SRF_MAX | SAHPI_SRF_MIN,
                                        .Max = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 125,
                                                        }
                                                },
                                        },
                                        .Min = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 0,
                                                        }
                                                },
                                        },
                                },
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_TRUE,
                                .TholdCapabilities = SAHPI_STC_INTERPRETED,
                                .ReadThold = 0, /* No Readable thresholds */
                                /* Default HDW thresholds: Warning=60; Warning Reset=55 */
                        },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_UNSPECIFIED,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                                .DeassertEvents = SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        },
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .convert_snmpstr = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                .oid = ".1.3.6.1.4.1.2.3.51.2.2.1.1.2.0",
                        },
                        .event_array = {
                                {
                                        .event = "0001C500", /* EN_CUTOFF_HI_OVER_TEMP_SP_CARD */
                                        .event_state = SAHPI_ES_UPPER_CRIT | SAHPI_ES_UPPER_MAJOR |
                                                       SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                },
                                {
                                        .event = "0001D400", /* EN_PFA_HI_OVER_TEMP_SP_CARD */
                                        .event_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UNSPECIFIED,
                                },
                                {},
                        },
                },
                .comment = "Management module temperature sensor"
        },
        /* 1.8V voltage sensor on Management Module */
        {
                .sensor = {
                        .Num = 5,
                        .Type = SAHPI_VOLTAGE,
                        .Category = SAHPI_EC_THRESHOLD,
                        .EventCtrl = SAHPI_SEC_GLOBAL_DISABLE,
                        .Events = SAHPI_ES_UNSPECIFIED |
                                  SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_CRIT |
                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_INTERPRETED,
                                .IsNumeric = SAHPI_TRUE,
                                .SignFormat = SAHPI_SDF_UNSIGNED,
                                .BaseUnits = SAHPI_SU_VOLTS,
                                .ModifierUnits = SAHPI_SU_UNSPECIFIED,
                                .ModifierUse = SAHPI_SMUU_NONE,
                                .FactorsStatic = SAHPI_TRUE,
                                .Factors = {
                                        .Linearization = SAHPI_SL_LINEAR,
                                },
                                .Percentage = SAHPI_FALSE,
                                .Range = {
                                        .Flags = SAHPI_SRF_MAX | SAHPI_SRF_MIN | SAHPI_SRF_NOMINAL,
                                        .Max = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 4.4,
                                                        }
                                                },
                                        },
                                        .Nominal = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 1.8,
                                                        }
                                                },
                                        },
                                        .Min = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 0,
                                                        }
                                                },
                                        },
                                },
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_TRUE,
                                .TholdCapabilities = SAHPI_STC_INTERPRETED,
                                .ReadThold = SAHPI_STM_LOW_MAJOR | SAHPI_STM_UP_MAJOR |
                                             SAHPI_STM_LOW_HYSTERESIS | SAHPI_STM_UP_HYSTERESIS,
                                .FixedThold = SAHPI_STM_LOW_MAJOR | SAHPI_STM_UP_MAJOR |
                                              SAHPI_STM_LOW_HYSTERESIS | SAHPI_STM_UP_HYSTERESIS,
                                /* Default HDW thresholds:
                                   Warning 1.62<>1.89; Warning Reset 1.86<>1.74 */
                         },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_UNSPECIFIED,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_CRIT |
                                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                                .DeassertEvents = SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_CRIT |
                                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        },
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .convert_snmpstr = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                .oid = ".1.3.6.1.4.1.2.3.51.2.2.2.1.8.0",
                                .threshold_oids = {
                                        .InterpretedThresholds = {
                                                .OidLowMajor = ".1.3.6.1.4.1.2.3.51.2.2.20.2.1.1.10.6",
                                                .OidUpMajor  = ".1.3.6.1.4.1.2.3.51.2.2.20.2.1.1.6.6",
                                                .OidUpHysteresis  = ".1.3.6.1.4.1.2.3.51.2.2.20.2.1.1.7.6",
                                                .OidLowHysteresis = ".1.3.6.1.4.1.2.3.51.2.2.20.2.1.1.11.6",
                                        },
                                },
                        },
                        .event_array = {
                                {
                                        .event = "0807A480", /* EN_CUTOFF_HI_FAULT_1_8V */
                                        .event_state = SAHPI_ES_UPPER_CRIT | SAHPI_ES_UPPER_MAJOR |
                                                       SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                },
                                {
                                        .event = "0807A880", /* EN_CUTOFF_LO_FAULT_1_8V */
                                        .event_state = SAHPI_ES_LOWER_CRIT | SAHPI_ES_LOWER_MAJOR |
                                                       SAHPI_ES_LOWER_MINOR,
                                        .recovery_state = SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_MINOR,
                                },
                                {
                                        .event = "0807B400", /* EN_PFA_HI_FAULT_1_8V */
                                        .event_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UNSPECIFIED,
                                },
                                {
                                        .event = "0807B800", /* EN_PFA_LO_FAULT_1_8V */
                                        .event_state = SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_MINOR,
                                        .recovery_state = SAHPI_ES_UNSPECIFIED,
                                },
                                {},
                        },
                },
                .comment = "Chassis 1.8 volt sensor"
        },
        /* 2.5V voltage sensor on Management Module */
        {
                .sensor = {
                        .Num = 6,
                        .Type = SAHPI_VOLTAGE,
                        .Category = SAHPI_EC_THRESHOLD,
                        .EventCtrl = SAHPI_SEC_GLOBAL_DISABLE,
                        .Events = SAHPI_ES_UNSPECIFIED |
                                  SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_CRIT |
                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_INTERPRETED,
                                .IsNumeric = SAHPI_TRUE,
                                .SignFormat = SAHPI_SDF_UNSIGNED,
                                .BaseUnits = SAHPI_SU_VOLTS,
                                .ModifierUnits = SAHPI_SU_UNSPECIFIED,
                                .ModifierUse = SAHPI_SMUU_NONE,
                                .FactorsStatic = SAHPI_TRUE,
                                .Factors = {
                                        .Linearization = SAHPI_SL_LINEAR,
                                },
                                .Percentage = SAHPI_FALSE,
                                .Range = {
                                        .Flags = SAHPI_SRF_MAX | SAHPI_SRF_MIN | SAHPI_SRF_NOMINAL,
                                        .Max = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 4.4,
                                                        }
                                                },
                                        },
                                        .Nominal = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 2.5,
                                                        }
                                                },
                                        },
                                        .Min = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 0,
                                                        }
                                                },
                                        },
                                },
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_TRUE,
                                .TholdCapabilities = SAHPI_STC_INTERPRETED,
                                .ReadThold = SAHPI_STM_LOW_MAJOR | SAHPI_STM_UP_MAJOR |
                                             SAHPI_STM_LOW_HYSTERESIS | SAHPI_STM_UP_HYSTERESIS,
                                .FixedThold = SAHPI_STM_LOW_MAJOR | SAHPI_STM_UP_MAJOR |
                                              SAHPI_STM_LOW_HYSTERESIS | SAHPI_STM_UP_HYSTERESIS,
                                /* Default HDW thresholds:
                                   Warning 2.25<>2.63; Warning Reset 2.58<>2.42 */
                        },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_UNSPECIFIED,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_CRIT |
                                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                                .DeassertEvents = SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_CRIT |
                                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        },
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .convert_snmpstr = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                .oid = ".1.3.6.1.4.1.2.3.51.2.2.2.1.6.0",
                                .threshold_oids = {
                                        .InterpretedThresholds = {
                                                .OidLowMajor = ".1.3.6.1.4.1.2.3.51.2.2.20.2.1.1.10.5",
                                                .OidUpMajor  = ".1.3.6.1.4.1.2.3.51.2.2.20.2.1.1.6.5",
                                                .OidUpHysteresis  = ".1.3.6.1.4.1.2.3.51.2.2.20.2.1.1.7.5",
                                                .OidLowHysteresis = ".1.3.6.1.4.1.2.3.51.2.2.20.2.1.1.11.5",
                                        },
                                },
                        },
                        .event_array = {
                                {
                                        .event = "08030480", /* EN_CUTOFF_HI_FAULT_2_5V */
                                        .event_state = SAHPI_ES_UPPER_CRIT | SAHPI_ES_UPPER_MAJOR |
                                                       SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                },
                                {
                                        .event = "08030880", /* EN_CUTOFF_LO_FAULT_2_5V */
                                        .event_state = SAHPI_ES_LOWER_CRIT | SAHPI_ES_LOWER_MAJOR |
                                                       SAHPI_ES_LOWER_MINOR,
                                        .recovery_state = SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_MINOR,
                                },
                                {
                                        .event = "FF031480", /* EN_PFA_HI_FAULT_2_5V */
                                        .event_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UNSPECIFIED,
                                },
                                {
                                        .event = "FF031880", /* EN_PFA_LO_FAULT_2_5V */
                                        .event_state = SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_MINOR,
                                        .recovery_state = SAHPI_ES_UNSPECIFIED,
                                },
                                {},
                        },
                },
                .comment = "Chassis 2.5 volt sensor"
        },
        /* 3.3V voltage sensor on Management Module */
        {
                .sensor = {
                        .Num = 7,
                        .Type = SAHPI_VOLTAGE,
                        .Category = SAHPI_EC_THRESHOLD,
                        .EventCtrl = SAHPI_SEC_GLOBAL_DISABLE,
                        .Events = SAHPI_ES_UNSPECIFIED |
                                  SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_CRIT |
                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_INTERPRETED,
                                .IsNumeric = SAHPI_TRUE,
                                .SignFormat = SAHPI_SDF_UNSIGNED,
                                .BaseUnits = SAHPI_SU_VOLTS,
                                .ModifierUnits = SAHPI_SU_UNSPECIFIED,
                                .ModifierUse = SAHPI_SMUU_NONE,
                                .FactorsStatic = SAHPI_TRUE,
                                .Factors = {
                                        .Linearization = SAHPI_SL_LINEAR,
                                },
                                .Percentage = SAHPI_FALSE,
                                .Range = {
                                        .Flags = SAHPI_SRF_MAX | SAHPI_SRF_MIN | SAHPI_SRF_NOMINAL,
                                        .Max = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 3.6,
                                                        }
                                                },
                                        },
                                        .Nominal = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 3.3,
                                                        }
                                                },
                                        },
                                        .Min = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 0,
                                                        }
                                                },
                                        },
                                },
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_TRUE,
                                .TholdCapabilities = SAHPI_STC_INTERPRETED,
                                .ReadThold = SAHPI_STM_LOW_MAJOR | SAHPI_STM_UP_MAJOR |
                                             SAHPI_STM_LOW_HYSTERESIS | SAHPI_STM_UP_HYSTERESIS,
                                .FixedThold = SAHPI_STM_LOW_MAJOR | SAHPI_STM_UP_MAJOR |
                                              SAHPI_STM_LOW_HYSTERESIS | SAHPI_STM_UP_HYSTERESIS,
                                /* Default HDW thresholds:
                                   Warning 3.00<>3.47; Warning Reset 3.40<>3.20 */
                        },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_UNSPECIFIED,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_CRIT |
                                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                                .DeassertEvents = SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_CRIT |
                                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        },
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .convert_snmpstr = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                .oid = ".1.3.6.1.4.1.2.3.51.2.2.2.1.2.0",
                                .threshold_oids = {
                                        .InterpretedThresholds = {
                                                .OidLowMajor = ".1.3.6.1.4.1.2.3.51.2.2.20.2.1.1.10.2",
                                                .OidUpMajor  = ".1.3.6.1.4.1.2.3.51.2.2.20.2.1.1.6.2",
                                                .OidUpHysteresis  = ".1.3.6.1.4.1.2.3.51.2.2.20.2.1.1.7.2",
                                                .OidLowHysteresis = ".1.3.6.1.4.1.2.3.51.2.2.20.2.1.1.11.2",
                                        },
                                },
                        },
                        .event_array = {
                                {
                                        .event = "08032480", /* EN_CUTOFF_HI_FAULT_3_35V */
                                        .event_state = SAHPI_ES_UPPER_CRIT | SAHPI_ES_UPPER_MAJOR |
                                                       SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                },
                                {
                                        .event = "08032880", /* EN_CUTOFF_LO_FAULT_3_35V */
                                        .event_state = SAHPI_ES_LOWER_CRIT | SAHPI_ES_LOWER_MAJOR |
                                                       SAHPI_ES_LOWER_MINOR,
                                        .recovery_state = SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_MINOR,
                                },
                                {
                                        .event = "FF033480", /* EN_PFA_HI_FAULT_3_35V */
                                        .event_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UNSPECIFIED,
                                },
                                {
                                        .event = "FF033880", /* EN_PFA_LO_FAULT_3_35V */
                                        .event_state = SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_MINOR,
                                        .recovery_state = SAHPI_ES_UNSPECIFIED,
                                },
                                {},
                        },
                },
                .comment = "Chassis 3.3 volt sensor"
        },
        /* 5V voltage sensor on Management Module */
        {
                .sensor = {
                        .Num = 8,
                        .Type = SAHPI_VOLTAGE,
                        .Category = SAHPI_EC_THRESHOLD,
                        .EventCtrl = SAHPI_SEC_GLOBAL_DISABLE,
                        .Events = SAHPI_ES_UNSPECIFIED |
                                  SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_CRIT |
                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_INTERPRETED,
                                .IsNumeric = SAHPI_TRUE,
                                .SignFormat = SAHPI_SDF_UNSIGNED,
                                .BaseUnits = SAHPI_SU_VOLTS,
                                .ModifierUnits = SAHPI_SU_UNSPECIFIED,
                                .ModifierUse = SAHPI_SMUU_NONE,
                                .FactorsStatic = SAHPI_TRUE,
                                .Factors = {
                                        .Linearization = SAHPI_SL_LINEAR,
                                },
                                .Percentage = SAHPI_FALSE,
                                .Range = {
                                        .Flags = SAHPI_SRF_MAX | SAHPI_SRF_MIN | SAHPI_SRF_NOMINAL,
                                        .Max = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 6.7,
                                                        }
                                                },
                                        },
                                        .Nominal = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 5,
                                                        }
                                                },
                                        },
                                        .Min = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 0,
                                                        }
                                                },
                                        },
                                },
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_TRUE,
                                .TholdCapabilities = SAHPI_STC_INTERPRETED,
                                .ReadThold = SAHPI_STM_LOW_MAJOR | SAHPI_STM_UP_MAJOR |
                                             SAHPI_STM_LOW_HYSTERESIS | SAHPI_STM_UP_HYSTERESIS,
                                .FixedThold = SAHPI_STM_LOW_MAJOR | SAHPI_STM_UP_MAJOR |
                                              SAHPI_STM_LOW_HYSTERESIS | SAHPI_STM_UP_HYSTERESIS,
                                /* Default HDW thresholds:
                                   Warning 4.50<>5.25; Warning Reset 5.15<>4.85 */
                         },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_UNSPECIFIED,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_CRIT |
                                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                                .DeassertEvents = SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_CRIT |
                                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        },
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .convert_snmpstr = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                .oid = ".1.3.6.1.4.1.2.3.51.2.2.2.1.1.0",
                                .threshold_oids = {
                                        .InterpretedThresholds = {
                                                .OidLowMajor = ".1.3.6.1.4.1.2.3.51.2.2.20.2.1.1.10.1",
                                                .OidUpMajor  = ".1.3.6.1.4.1.2.3.51.2.2.20.2.1.1.6.1",
                                                .OidUpHysteresis  = ".1.3.6.1.4.1.2.3.51.2.2.20.2.1.1.7.1",
                                                .OidLowHysteresis = ".1.3.6.1.4.1.2.3.51.2.2.20.2.1.1.11.1",
                                        },
                                },
                        },
                        .event_array = {
                                {
                                        .event = "06034480", /* EN_CUTOFF_HI_FAULT_PLANAR_5V */
                                        .event_state = SAHPI_ES_UPPER_CRIT | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                },
                                {
                                        .event = "06034800", /* EN_CUTOFF_LO_FAULT_PLANAR_5V */
                                        .event_state = SAHPI_ES_LOWER_CRIT | SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_MINOR,
                                        .recovery_state = SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_MINOR,
                                },
                                {
                                        .event = "06035500", /* EN_PFA_HI_FAULT_PLANAR_5V */
                                        .event_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UNSPECIFIED,
                                },
                                {
                                        .event = "06035800", /* EN_PFA_LO_FAULT_PLANAR_5V */
                                        .event_state = SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_MINOR,
                                        .recovery_state = SAHPI_ES_UNSPECIFIED,
                                },
                                {},
                        },
                },
                .comment = "Chassis 5 volt sensor"
        },
        /* -5V voltage sensor on Management Module */
        {
                .sensor = {
                        .Num = 9,
                        .Type = SAHPI_VOLTAGE,
                        .Category = SAHPI_EC_THRESHOLD,
                        .EventCtrl = SAHPI_SEC_GLOBAL_DISABLE,
                        .Events = SAHPI_ES_UNSPECIFIED |
                                  SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_CRIT |
                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_INTERPRETED,
                                .IsNumeric = SAHPI_TRUE,
                                .SignFormat = SAHPI_SDF_UNSIGNED,
                                .BaseUnits = SAHPI_SU_VOLTS,
                                .ModifierUnits = SAHPI_SU_UNSPECIFIED,
                                .ModifierUse = SAHPI_SMUU_NONE,
                                .FactorsStatic = SAHPI_TRUE,
                                .Factors = {
                                        .Linearization = SAHPI_SL_LINEAR,
                                },
                                .Percentage = SAHPI_FALSE,
                                .Range = {
                                        .Flags = SAHPI_SRF_MAX | SAHPI_SRF_MIN | SAHPI_SRF_NOMINAL,
                                        .Max = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = -6.7,
                                                        }
                                                },
                                        },
                                        .Nominal = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = -5,
                                                        }
                                                },
                                        },
                                        .Min = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 0,
                                                        }
                                                },
                                        },
                                },
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_TRUE,
                                .TholdCapabilities = SAHPI_STC_INTERPRETED,
                                .ReadThold = SAHPI_STM_LOW_MAJOR | SAHPI_STM_UP_MAJOR |
                                             SAHPI_STM_LOW_HYSTERESIS | SAHPI_STM_UP_HYSTERESIS,
                                .FixedThold = SAHPI_STM_LOW_MAJOR | SAHPI_STM_UP_MAJOR |
                                              SAHPI_STM_LOW_HYSTERESIS | SAHPI_STM_UP_HYSTERESIS,
                                /* Default HDW thresholds:
                                   Warning -5.50<>-4.75; Warning Reset -4.85<>-5.15 */
                         },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_UNSPECIFIED,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_CRIT |
                                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                                .DeassertEvents = SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_CRIT |
                                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        },
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .convert_snmpstr = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                .oid = ".1.3.6.1.4.1.2.3.51.2.2.2.1.5.0",
                                .threshold_oids = {
                                        .InterpretedThresholds = {
                                                .OidLowMajor = ".1.3.6.1.4.1.2.3.51.2.2.20.2.1.1.10.4",
                                                .OidUpMajor  = ".1.3.6.1.4.1.2.3.51.2.2.20.2.1.1.6.4",
                                                .OidUpHysteresis  = ".1.3.6.1.4.1.2.3.51.2.2.20.2.1.1.7.4",
                                                .OidLowHysteresis = ".1.3.6.1.4.1.2.3.51.2.2.20.2.1.1.11.4",
                                        },
                                },
                        },
                        .event_array = {
                                {
                                        .event = "0803C480", /* EN_CUTOFF_HI_FAULT_N5V */
                                        .event_state = SAHPI_ES_UPPER_CRIT| SAHPI_ES_UPPER_MAJOR |
                                                       SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                },
                                {
                                        .event = "0803C800", /* EN_CUTOFF_LO_FAULT_N5V */
                                        .event_state = SAHPI_ES_LOWER_CRIT | SAHPI_ES_LOWER_MAJOR |
                                                       SAHPI_ES_LOWER_MINOR,
                                        .recovery_state = SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_MINOR,
                                },
                                {
                                        .event = "0803D500", /* EN_PFA_HI_FAULT_N5V */
                                        .event_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UNSPECIFIED,
                                },
                                {
                                        .event = "0803D800", /* EN_PFA_LO_FAULT_N5V */
                                        .event_state = SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_MINOR,
                                        .recovery_state = SAHPI_ES_UNSPECIFIED,
                                },
                                {},
                        },
                },
                .comment = "Chassis -5 volt sensor"
        },
        /* 12V voltage sensor on Management Module */
        {
                .sensor = {
                        .Num = 10,
                        .Type = SAHPI_VOLTAGE,
                        .Category = SAHPI_EC_THRESHOLD,
                        .EventCtrl = SAHPI_SEC_GLOBAL_DISABLE,
                        .Events = SAHPI_ES_UNSPECIFIED |
                                  SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_CRIT |
                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_INTERPRETED,
                                .IsNumeric = SAHPI_TRUE,
                                .SignFormat = SAHPI_SDF_UNSIGNED,
                                .BaseUnits = SAHPI_SU_VOLTS,
                                .ModifierUnits = SAHPI_SU_UNSPECIFIED,
                                .ModifierUse = SAHPI_SMUU_NONE,
                                .FactorsStatic = SAHPI_TRUE,
                                .Factors = {
                                        .Linearization = SAHPI_SL_LINEAR,
                                },
                                .Percentage = SAHPI_FALSE,
                                .Range = {
                                        .Flags = SAHPI_SRF_MAX | SAHPI_SRF_MIN | SAHPI_SRF_NOMINAL,
                                        .Max = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 16,
                                                        }
                                                },
                                        },
                                        .Nominal = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 12,
                                                        }
                                                },
                                        },
                                        .Min = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 0,
                                                        }
                                                },
                                        },
                                },
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_TRUE,
                                .TholdCapabilities = SAHPI_STC_INTERPRETED,
                                .ReadThold = SAHPI_STM_LOW_MAJOR | SAHPI_STM_UP_MAJOR |
                                             SAHPI_STM_LOW_HYSTERESIS | SAHPI_STM_UP_HYSTERESIS,
                                .FixedThold = SAHPI_STM_LOW_MAJOR | SAHPI_STM_UP_MAJOR |
                                              SAHPI_STM_LOW_HYSTERESIS | SAHPI_STM_UP_HYSTERESIS,
                                /* Default HDW thresholds:
                                   Warning 10.80<>12.60; Warning Reset 12.34<>11.64 */
                        },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_UNSPECIFIED,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_CRIT |
                                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                                .DeassertEvents = SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_CRIT |
                                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        },
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .convert_snmpstr = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                .oid = ".1.3.6.1.4.1.2.3.51.2.2.2.1.3.0",
                                .threshold_oids = {
                                        .InterpretedThresholds = {
                                                .OidLowMajor = ".1.3.6.1.4.1.2.3.51.2.2.20.2.1.1.10.3",
                                                .OidUpMajor  = ".1.3.6.1.4.1.2.3.51.2.2.20.2.1.1.6.3",
                                                .OidUpHysteresis  = ".1.3.6.1.4.1.2.3.51.2.2.20.2.1.1.7.3",
                                                .OidLowHysteresis = ".1.3.6.1.4.1.2.3.51.2.2.20.2.1.1.11.3",
                                        },
                                },
                        },
                        .event_array = {
                                {
                                        .event = "06036480", /* EN_CUTOFF_HI_FAULT_12V_PLANAR */
                                        .event_state = SAHPI_ES_UPPER_CRIT | SAHPI_ES_UPPER_MAJOR |
                                                       SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                },
                                {
                                        .event = "06036800", /* EN_CUTOFF_LO_FAULT_12V_PLANAR */
                                        .event_state = SAHPI_ES_LOWER_CRIT | SAHPI_ES_LOWER_MAJOR |
                                                       SAHPI_ES_LOWER_MINOR,
                                        .recovery_state = SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_MINOR,
                                },
                                {
                                        .event = "FF037500", /* EN_PFA_HI_FAULT_12V_PLANAR */
                                        .event_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UNSPECIFIED,
                                },
                                {
                                        .event = "FF037800", /* EN_PFA_LO_FAULT_12V_PLANAR */
                                        .event_state = SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_MINOR,
                                        .recovery_state = SAHPI_ES_UNSPECIFIED,
                                },
                                {},
                        },
                },
                .comment = "Chassis 12 volt sensor"
        },
        /* Management module redundancy sensor */
        {
                .sensor = {
                        .Num = 11,
                        .Type = SAHPI_PLATFORM_ALERT,
                        .Category = SAHPI_EC_REDUNDANCY,
                        .EventCtrl = SAHPI_SEC_GLOBAL_DISABLE,
                        .Events = SAHPI_ES_UNSPECIFIED | SAHPI_ES_REDUNDANCY_LOST | SAHPI_ES_FULLY_REDUNDANT,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_EVENT_STATE,
                                .IsNumeric = SAHPI_FALSE,
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_FALSE,
                        },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_UNSPECIFIED,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_REDUNDANCY_LOST,
                                .DeassertEvents = SAHPI_ES_REDUNDANCY_LOST,
                        },
                        .event_array = {
                                {
                                        .event = "00284000", /* EN_MM_NON_REDUNDANT */
                                        .event_state = SAHPI_ES_REDUNDANCY_LOST,
                                        .recovery_state = SAHPI_ES_FULLY_REDUNDANT,
                                },
                                {},
                        },
                },
                .comment = "Chassis management module redundancy sensor"
        },
        /* Switch module redundancy sensor */
        {
                .sensor = {
                        .Num = 12,
                        .Type = SAHPI_PLATFORM_ALERT,
                        .Category = SAHPI_EC_REDUNDANCY,
                        .EventCtrl = SAHPI_SEC_GLOBAL_DISABLE,
                        .Events = SAHPI_ES_UNSPECIFIED | SAHPI_ES_REDUNDANCY_LOST | SAHPI_ES_FULLY_REDUNDANT,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_EVENT_STATE,
                                .IsNumeric = SAHPI_FALSE,
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_FALSE,
                        },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_UNSPECIFIED,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_REDUNDANCY_LOST,
                                .DeassertEvents = SAHPI_ES_REDUNDANCY_LOST,
                        },
                        .event_array = {
                                {
                                        .event = "0EA16000", /* EN_SWITCH_NON_REDUNDANT */
                                        .event_state = SAHPI_ES_REDUNDANCY_LOST,
                                        .recovery_state = SAHPI_ES_FULLY_REDUNDANT,
                                },
                                {},
                        },
                },
                .comment = "Chassis switch module redundancy sensor"
        },
        /* Power module redundancy sensor */
        {
                .sensor = {
                        .Num = 13,
                        .Type = SAHPI_PLATFORM_ALERT,
                        .Category = SAHPI_EC_REDUNDANCY,
                        .EventCtrl = SAHPI_SEC_GLOBAL_DISABLE,
                        .Events = SAHPI_ES_UNSPECIFIED | SAHPI_ES_REDUNDANCY_LOST | SAHPI_ES_FULLY_REDUNDANT,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_EVENT_STATE,
                                .IsNumeric = SAHPI_FALSE,
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_FALSE,
                        },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_UNSPECIFIED,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_REDUNDANCY_LOST,
                                .DeassertEvents = SAHPI_ES_REDUNDANCY_LOST,
                        },
                        .event_array = {
                                {
                                        .event = "08080001", /* EN_NR_PWR_SUPPLY */
                                        .event_state = SAHPI_ES_REDUNDANCY_LOST,
                                        .recovery_state = SAHPI_ES_FULLY_REDUNDANT,
                                },
                                {},
                        },
                },
                .comment = "Chassis power module redundancy sensor"
        },

        {} /* Terminate array with a null element */
};

/***************
 * Blade Sensors
 ***************/

struct snmp_bc_sensor snmp_bc_blade_sensors[] = {

        /* Blade Error LED */
        {
                .sensor = {
                        .Num = 1,
                        .Type = SAHPI_PLATFORM_VIOLATION,
                        .Category = SAHPI_EC_SEVERITY,
                        .EventCtrl = SAHPI_SEC_NO_EVENTS,
                        .Events = SAHPI_ES_OK | SAHPI_ES_CRITICAL,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_EVENT_STATE | SAHPI_SRF_RAW,
                                .IsNumeric = SAHPI_TRUE,
                                .SignFormat = SAHPI_SDF_UNSIGNED,
                                .BaseUnits = SAHPI_SU_UNSPECIFIED,
                                .ModifierUnits = SAHPI_SU_UNSPECIFIED,
                                .ModifierUse = SAHPI_SMUU_NONE,
                                .FactorsStatic = SAHPI_TRUE,
                                .Factors = {
                                        .M_Factor = 1,
                                        .Linearization = SAHPI_SL_NONLINEAR,
                                },
                                .Percentage = SAHPI_FALSE,
                                .Range = {
                                        .Flags = SAHPI_SRF_MIN | SAHPI_SRF_MAX,
                                        .Max = {
                                                .ValuesPresent = SAHPI_SRF_EVENT_STATE | SAHPI_SRF_RAW,
                                                .Raw = 1,
                                                .EventStatus = {
                                                        .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                                        .EventStatus = SAHPI_ES_CRITICAL,
                                                }
                                        },
                                        .Min = {
                                                .ValuesPresent = SAHPI_SRF_EVENT_STATE | SAHPI_SRF_RAW,
                                                .Raw = 0,
                                                .EventStatus = {
                                                        .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                                        .EventStatus = SAHPI_ES_OK,
                                                }
                                        }
                                }
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_FALSE
                        },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_OK,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_OK | SAHPI_ES_CRITICAL,
                                .DeassertEvents = SAHPI_ES_OK | SAHPI_ES_CRITICAL,
                        },
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .convert_snmpstr = -1,
                                .oid = ".1.3.6.1.4.1.2.3.51.2.2.8.2.1.1.7.x",
                        },
                        .event_array = {
                                {},
                        },
                },
                .comment = "Blade LED - Error"
        },
        /*  Blade KVM Usage LED */
        {
                .sensor = {
                        .Num = 2,
                        .Type = SAHPI_BUTTON,
                        .Category = SAHPI_EC_USAGE,
                        .EventCtrl = SAHPI_SEC_NO_EVENTS,
                        .Events = SAHPI_ES_UNSPECIFIED | SAHPI_ES_IDLE | SAHPI_ES_ACTIVE | SAHPI_ES_BUSY,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_EVENT_STATE | SAHPI_SRF_RAW,
                                .IsNumeric = SAHPI_TRUE,
                                .SignFormat = SAHPI_SDF_UNSIGNED,
                                .BaseUnits = SAHPI_SU_UNSPECIFIED,
                                .ModifierUnits = SAHPI_SU_UNSPECIFIED,
                                .ModifierUse = SAHPI_SMUU_NONE,
                                .FactorsStatic = SAHPI_TRUE,
                                .Factors = {
                                        .M_Factor = 1,
                                        .Linearization = SAHPI_SL_NONLINEAR,
                                },
                                .Percentage = SAHPI_FALSE,
                                .Range = {
                                        .Flags = SAHPI_SRF_MIN | SAHPI_SRF_NOMINAL |SAHPI_SRF_MAX,
                                        .Max = {
                                                .ValuesPresent = SAHPI_SRF_EVENT_STATE | SAHPI_SRF_RAW,
                                                .Raw = 2,
                                                .EventStatus = {
                                                        .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                                        .EventStatus = SAHPI_ES_BUSY
                                                }
                                        },
                                        .Nominal = {
                                                .ValuesPresent = SAHPI_SRF_EVENT_STATE | SAHPI_SRF_RAW,
                                                .Raw = 1,
                                                .EventStatus = {
                                                        .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                                        .EventStatus = SAHPI_ES_ACTIVE
                                                }
                                        },
                                        .Min = {
                                                .ValuesPresent = SAHPI_SRF_EVENT_STATE | SAHPI_SRF_RAW,
                                                .Raw = 0,
                                                .EventStatus = {
                                                        .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                                        .EventStatus = SAHPI_ES_IDLE
                                                }
                                        }
                                }
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_FALSE
                        },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_UNSPECIFIED,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_IDLE | SAHPI_ES_ACTIVE | SAHPI_ES_BUSY,
                                .DeassertEvents = SAHPI_ES_IDLE | SAHPI_ES_ACTIVE | SAHPI_ES_BUSY,
                        },
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .convert_snmpstr = -1,
                                .oid = ".1.3.6.1.4.1.2.3.51.2.2.8.2.1.1.9.x",
                        },
                        .event_array = {
                                {},
                        },
                },
                .comment = "Blade LED - KVM usage"
        },
        /*  Blade Media Tray Usage LED */
        {
                .sensor = {
                        .Num = 3,
                        .Type = SAHPI_BUTTON,
                        .Category = SAHPI_EC_USAGE,
                        .EventCtrl = SAHPI_SEC_NO_EVENTS,
                        .Events = SAHPI_ES_UNSPECIFIED | SAHPI_ES_IDLE | SAHPI_ES_ACTIVE | SAHPI_ES_BUSY,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_EVENT_STATE | SAHPI_SRF_RAW,
                                .IsNumeric = SAHPI_TRUE,
                                .SignFormat = SAHPI_SDF_UNSIGNED,
                                .BaseUnits = SAHPI_SU_UNSPECIFIED,
                                .ModifierUnits = SAHPI_SU_UNSPECIFIED,
                                .ModifierUse = SAHPI_SMUU_NONE,
                                .FactorsStatic = SAHPI_TRUE,
                                .Factors = {
                                        .M_Factor = 1,
                                        .Linearization = SAHPI_SL_NONLINEAR,
                                },
                                .Percentage = SAHPI_FALSE,
                                .Range = {
                                        .Flags = SAHPI_SRF_MIN | SAHPI_SRF_NOMINAL |SAHPI_SRF_MAX,
                                        .Max = {
                                                .ValuesPresent = SAHPI_SRF_EVENT_STATE | SAHPI_SRF_RAW,
                                                .Raw = 2,
                                                .EventStatus = {
                                                        .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                                        .EventStatus = SAHPI_ES_BUSY
                                                }
                                        },
                                        .Nominal = {
                                                .ValuesPresent = SAHPI_SRF_EVENT_STATE | SAHPI_SRF_RAW,
                                                .Raw = 1,
                                                .EventStatus = {
                                                        .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                                        .EventStatus = SAHPI_ES_ACTIVE
                                                }
                                        },
                                        .Min = {
                                                .ValuesPresent = SAHPI_SRF_EVENT_STATE | SAHPI_SRF_RAW,
                                                .Raw = 0,
                                                .EventStatus = {
                                                        .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                                        .EventStatus = SAHPI_ES_IDLE
                                                }
                                        }
                                }
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_FALSE
                        },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_UNSPECIFIED,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_IDLE | SAHPI_ES_ACTIVE | SAHPI_ES_BUSY,
                                .DeassertEvents = SAHPI_ES_IDLE | SAHPI_ES_ACTIVE | SAHPI_ES_BUSY,
                        },
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .convert_snmpstr = -1,
                                .oid = ".1.3.6.1.4.1.2.3.51.2.2.8.2.1.1.10.x",
                        },
                        .event_array = {
                                {},
                        },
                },
                .comment = "Blade LED - Media Tray usage"
        },
        /* CPU 1 thermal sensor */
        {
                .sensor = {
                        .Num = 4,
                        .Type = SAHPI_TEMPERATURE,
                        .Category = SAHPI_EC_THRESHOLD,
                        .EventCtrl = SAHPI_SEC_GLOBAL_DISABLE,
                        .Events = SAHPI_ES_UNSPECIFIED |
                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_INTERPRETED,
                                .IsNumeric = SAHPI_TRUE,
                                .SignFormat = SAHPI_SDF_UNSIGNED,
                                .BaseUnits = SAHPI_SU_DEGREES_C,
                                .ModifierUnits = SAHPI_SU_UNSPECIFIED,
                                .ModifierUse = SAHPI_SMUU_NONE,
                                .FactorsStatic = SAHPI_TRUE,
                                .Factors = {
                                        .Linearization = SAHPI_SL_LINEAR,
                                },
                                .Percentage = SAHPI_FALSE,
                                .Range = {
                                        .Flags = SAHPI_SRF_MAX | SAHPI_SRF_MIN,
                                        .Max = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 125,
                                                        }
                                                },
                                        },
                                        .Min = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 0,
                                                        }
                                                },
                                        },
                                },
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_TRUE,
                                .TholdCapabilities = SAHPI_STC_INTERPRETED,
                                .ReadThold  = SAHPI_STM_UP_MAJOR | SAHPI_STM_UP_CRIT,
                                .FixedThold = SAHPI_STM_UP_MAJOR | SAHPI_STM_UP_CRIT,
                        },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_UNSPECIFIED,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                                .DeassertEvents = SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        },
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .convert_snmpstr = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                .oid = ".1.3.6.1.4.1.2.3.51.2.22.1.5.3.1.6.x",
                                .threshold_oids = {
                                        .InterpretedThresholds = {
                                                .OidUpCrit   = ".1.3.6.1.4.1.2.3.51.2.22.1.5.4.1.6.x",
                                                .OidUpMajor  = ".1.3.6.1.4.1.2.3.51.2.22.1.5.4.1.7.x",
                                        },
                                },
                        },
                        .event_array = {
                                {
                                        .event = "0421C481", /* EN_CUTOFF_HI_OVER_TEMP_CPU1 */
                                        .event_state = SAHPI_ES_UPPER_CRIT | SAHPI_ES_UPPER_MAJOR |
                                                       SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                },
                                {
                                        .event = "0421D501", /* EN_PFA_HI_OVER_TEMP_CPU1 */
                                        .event_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UNSPECIFIED,
                                },
                                {
                                        .event = "0421C401", /* EN_PROC_HOT_CPU1 */
                                        .event_state = SAHPI_ES_UPPER_CRIT | SAHPI_ES_UPPER_MAJOR |
                                                       SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                },
                                {
                                        .event = "0421D081", /* EN_THERM_TRIP_CPU1 */
                                        .event_state = SAHPI_ES_UPPER_CRIT | SAHPI_ES_UPPER_MAJOR |
                                                       SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                },
                                {},
                        },
                },
                .comment = "Blade CPU 1 temperature sensor"
        },
        /* CPU 2 thermal sensor */
        {
                .sensor = {
                        .Num = 5,
                        .Type = SAHPI_TEMPERATURE,
                        .Category = SAHPI_EC_THRESHOLD,
                        .EventCtrl = SAHPI_SEC_GLOBAL_DISABLE,
                        .Events = SAHPI_ES_UNSPECIFIED |
                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_INTERPRETED,
                                .IsNumeric = SAHPI_TRUE,
                                .SignFormat = SAHPI_SDF_UNSIGNED,
                                .BaseUnits = SAHPI_SU_DEGREES_C,
                                .ModifierUnits = SAHPI_SU_UNSPECIFIED,
                                .ModifierUse = SAHPI_SMUU_NONE,
                                .FactorsStatic = SAHPI_TRUE,
                                .Factors = {
                                        .Linearization = SAHPI_SL_LINEAR,
                                },
                                .Percentage = SAHPI_FALSE,
                                .Range = {
                                        .Flags = SAHPI_SRF_MAX | SAHPI_SRF_MIN,
                                        .Max = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 125,
                                                        }
                                                },
                                        },
                                        .Min = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 0,
                                                        }
                                                },
                                        },
                                },
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_TRUE,
                                .TholdCapabilities = SAHPI_STC_INTERPRETED,
                                .ReadThold  = SAHPI_STM_UP_MAJOR | SAHPI_STM_UP_CRIT,
                                .FixedThold = SAHPI_STM_UP_MAJOR | SAHPI_STM_UP_CRIT,
                        },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_UNSPECIFIED,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                                .DeassertEvents = SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        },
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .convert_snmpstr = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                .oid = ".1.3.6.1.4.1.2.3.51.2.22.1.5.3.1.7.x",
                                .threshold_oids = {
                                        .InterpretedThresholds = {
                                                .OidUpCrit  = ".1.3.6.1.4.1.2.3.51.2.22.1.5.4.1.9.x",
                                                .OidUpMajor = ".1.3.6.1.4.1.2.3.51.2.22.1.5.4.1.10.x",
                                        },
                                },
                        },
                        .event_array = {
                                {
                                        .event = "0421C482", /* EN_CUTOFF_HI_OVER_TEMP_CPU2 */
                                        .event_state = SAHPI_ES_UPPER_CRIT | SAHPI_ES_UPPER_MAJOR |
                                                       SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                },
                                {
                                        .event = "0421D502", /* EN_PFA_HI_OVER_TEMP_CPU2 */
                                        .event_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UNSPECIFIED,
                                },
                                {
                                        .event = "0421C402", /* EN_PROC_HOT_CPU2 */
                                        .event_state = SAHPI_ES_UPPER_CRIT | SAHPI_ES_UPPER_MAJOR |
                                                       SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                },
                                {
                                        .event = "0421D082", /* EN_THERM_TRIP_CPU2 */
                                        .event_state = SAHPI_ES_UPPER_CRIT | SAHPI_ES_UPPER_MAJOR |
                                                       SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                },
                                {},
                        },
                },
                .comment = "Blade CPU 2 temperature sensor"
        },
        /* CPU 3 thermal sensor */
        {
                .sensor = {
                        .Num = 6,
                        .Type = SAHPI_TEMPERATURE,
                        .Category = SAHPI_EC_THRESHOLD,
                        .EventCtrl = SAHPI_SEC_GLOBAL_DISABLE,
                        .Events = SAHPI_ES_UNSPECIFIED |
                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_INTERPRETED,
                                .IsNumeric = SAHPI_TRUE,
                                .SignFormat = SAHPI_SDF_UNSIGNED,
                                .BaseUnits = SAHPI_SU_DEGREES_C,
                                .ModifierUnits = SAHPI_SU_UNSPECIFIED,
                                .ModifierUse = SAHPI_SMUU_NONE,
                                .FactorsStatic = SAHPI_TRUE,
                                .Factors = {
                                        .Linearization = SAHPI_SL_LINEAR,
                                },
                                .Percentage = SAHPI_FALSE,
                                .Range = {
                                        .Flags = SAHPI_SRF_MAX | SAHPI_SRF_MIN,
                                        .Max = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 125,
                                                        }
                                                },
                                        },
                                        .Min = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 0,
                                                        }
                                                },
                                        },
                                },
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_TRUE,
                                .TholdCapabilities = SAHPI_STC_INTERPRETED,
                                .ReadThold  = SAHPI_STM_UP_MAJOR | SAHPI_STM_UP_CRIT,
                                .FixedThold = SAHPI_STM_UP_MAJOR | SAHPI_STM_UP_CRIT,
                        },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_UNSPECIFIED,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                                .DeassertEvents = SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        },
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .convert_snmpstr = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                .oid = ".1.3.6.1.4.1.2.3.51.2.22.1.5.3.1.8.x",
                                .threshold_oids = {
                                        .InterpretedThresholds = {
                                                .OidUpCrit  = ".1.3.6.1.4.1.2.3.51.2.22.1.5.4.1.12.x",
                                                .OidUpMajor = ".1.3.6.1.4.1.2.3.51.2.22.1.5.4.1.13.x",
                                        },
                                },
                        },
                        .event_array = {
                                {
                                        .event = "0421C483", /* EN_CUTOFF_HI_OVER_TEMP_CPU3 */
                                        .event_state = SAHPI_ES_UPPER_CRIT | SAHPI_ES_UPPER_MAJOR |
                                                       SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                },
                                {
                                        .event = "0421D503", /* EN_PFA_HI_OVER_TEMP_CPU3 */
                                        .event_state = SAHPI_ES_UPPER_MAJOR  | SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UNSPECIFIED,
                                },
                                {
                                        .event = "0421C403", /* EN_PROC_HOT_CPU3 */
                                        .event_state = SAHPI_ES_UPPER_CRIT | SAHPI_ES_UPPER_MAJOR |
                                                       SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                },
                                {
                                        .event = "0421D083", /* EN_THERM_TRIP_CPU3 */
                                        .event_state = SAHPI_ES_UPPER_CRIT | SAHPI_ES_UPPER_MAJOR |
                                                       SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                },
                                {},
                        },
                },
                .comment = "Blade CPU 3 temperature sensor"
        },
        /* CPU 4 thermal sensor */
        {
                .sensor = {
                        .Num = 7,
                        .Type = SAHPI_TEMPERATURE,
                        .Category = SAHPI_EC_THRESHOLD,
                        .EventCtrl = SAHPI_SEC_GLOBAL_DISABLE,
                        .Events = SAHPI_ES_UNSPECIFIED |
                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_INTERPRETED,
                                .IsNumeric = SAHPI_TRUE,
                                .SignFormat = SAHPI_SDF_UNSIGNED,
                                .BaseUnits = SAHPI_SU_DEGREES_C,
                                .ModifierUnits = SAHPI_SU_UNSPECIFIED,
                                .ModifierUse = SAHPI_SMUU_NONE,
                                .FactorsStatic = SAHPI_TRUE,
                                .Factors = {
                                        .Linearization = SAHPI_SL_LINEAR,
                                },
                                .Percentage = SAHPI_FALSE,
                                .Range = {
                                        .Flags = SAHPI_SRF_MAX | SAHPI_SRF_MIN,
                                        .Max = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 125,
                                                        }
                                                },
                                        },
                                        .Min = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 0,
                                                        }
                                                },
                                        },
                                },
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_TRUE,
                                .TholdCapabilities = SAHPI_STC_INTERPRETED,
                                .ReadThold  = SAHPI_STM_UP_MAJOR | SAHPI_STM_UP_CRIT,
                                .FixedThold = SAHPI_STM_UP_MAJOR | SAHPI_STM_UP_CRIT,
                        },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_UNSPECIFIED,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                                .DeassertEvents = SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        },
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .convert_snmpstr = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                .oid = ".1.3.6.1.4.1.2.3.51.2.22.1.5.3.1.9.x",
                                .threshold_oids = {
                                        .InterpretedThresholds = {
                                                .OidUpCrit  = ".1.3.6.1.4.1.2.3.51.2.22.1.5.4.1.15.x",
                                                .OidUpMajor = ".1.3.6.1.4.1.2.3.51.2.22.1.5.4.1.16.x",
                                        },
                                },
                        },
                        .event_array = {
                                {
                                        .event = "0421C484", /* EN_CUTOFF_HI_OVER_TEMP_CPU4 */
                                        .event_state = SAHPI_ES_UPPER_CRIT | SAHPI_ES_UPPER_MAJOR |
                                                       SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                },
                                {
                                        .event = "0421D504", /* EN_PFA_HI_OVER_TEMP_CPU4 */
                                        .event_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UNSPECIFIED,
                                },
                                {
                                        .event = "0421C404", /* EN_PROC_HOT_CPU4 */
                                        .event_state = SAHPI_ES_UPPER_CRIT | SAHPI_ES_UPPER_MAJOR |
                                                       SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                },
                                {
                                        .event = "0421D084", /* EN_THERM_TRIP_CPU4 */
                                        .event_state = SAHPI_ES_UPPER_CRIT | SAHPI_ES_UPPER_MAJOR |
                                                       SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                },
                                {},
                        },
                },
                .comment = "Blade CPU 4 temperature sensor"
        },
        /* Blade's 1.25V voltage sensor */
        {
                .sensor = {
                        .Num = 8,
                        .Type = SAHPI_VOLTAGE,
                        .Category = SAHPI_EC_THRESHOLD,
                        .EventCtrl = SAHPI_SEC_GLOBAL_DISABLE,
                        .Events = SAHPI_ES_UNSPECIFIED |
                                  SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR |
                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_INTERPRETED,
                                .IsNumeric = SAHPI_TRUE,
                                .SignFormat = SAHPI_SDF_UNSIGNED,
                                .BaseUnits = SAHPI_SU_VOLTS,
                                .ModifierUnits = SAHPI_SU_UNSPECIFIED,
                                .ModifierUse = SAHPI_SMUU_NONE,
                                .FactorsStatic = SAHPI_TRUE,
                                .Factors = {
                                        .Linearization = SAHPI_SL_LINEAR,
                                },
                                .Percentage = SAHPI_FALSE,
                                .Range = {
                                        .Flags = SAHPI_SRF_MAX | SAHPI_SRF_MIN | SAHPI_SRF_NOMINAL,
                                        .Max = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 3.3,
                                                        }
                                                },
                                        },
                                        .Nominal = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 1.25,
                                                        }
                                                },
                                        },
                                        .Min = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 0,
                                                        }
                                                },
                                        },
                                },
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_TRUE,
                                .TholdCapabilities = SAHPI_STC_INTERPRETED,
                                .ReadThold  = SAHPI_STM_LOW_MAJOR | SAHPI_STM_UP_MAJOR,
                                .FixedThold = SAHPI_STM_LOW_MAJOR | SAHPI_STM_UP_MAJOR,
                                /* Default HDW thresholds: Warning 1.10<>1.4 */
                        },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_UNSPECIFIED,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR |
                                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR,
                                .DeassertEvents = SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR |
                                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR,
                        },
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .convert_snmpstr = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                .oid = ".1.3.6.1.4.1.2.3.51.2.22.1.5.5.1.12.x",
                                .threshold_oids = {
                                        .InterpretedThresholds = {
                                                .OidUpMajor  = ".1.3.6.1.4.1.2.3.51.2.22.1.5.6.1.18.x",
                                                .OidLowMajor = ".1.3.6.1.4.1.2.3.51.2.22.1.5.6.1.19.x",
                                        },
                                },
                        },
                        .event_array = {
                                {
                                        .event = "08001400", /* EN_PFA_HI_FAULT_1_25V */
                                        .event_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UNSPECIFIED,
                                },
                                {
                                        .event = "08001800", /* EN_PFA_LO_FAULT_1_25V */
                                        .event_state = SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_MINOR,
                                        .recovery_state = SAHPI_ES_UNSPECIFIED,
                                },
                                {},
                        },
                },
                .comment = "Blade 1.25 volt sensor"
        },
        /* Blade's 1.5V voltage sensor */
        {
                .sensor = {
                        .Num = 9,
                        .Type = SAHPI_VOLTAGE,
                        .Category = SAHPI_EC_THRESHOLD,
                        .EventCtrl = SAHPI_SEC_GLOBAL_DISABLE,
                        .Events = SAHPI_ES_UNSPECIFIED |
                                  SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_CRIT |
                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_INTERPRETED,
                                .IsNumeric = SAHPI_TRUE,
                                .SignFormat = SAHPI_SDF_UNSIGNED,
                                .BaseUnits = SAHPI_SU_VOLTS,
                                .ModifierUnits = SAHPI_SU_UNSPECIFIED,
                                .ModifierUse = SAHPI_SMUU_NONE,
                                .FactorsStatic = SAHPI_TRUE,
                                .Factors = {
                                        .Linearization = SAHPI_SL_LINEAR,
                                },
                                .Percentage = SAHPI_FALSE,
                                .Range = {
                                        .Flags = SAHPI_SRF_MAX | SAHPI_SRF_MIN | SAHPI_SRF_NOMINAL,
                                        .Max = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 4.4,
                                                        }
                                                },
                                        },
                                        .Nominal = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 1.5,
                                                        }
                                                },
                                        },
                                        .Min = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 0,
                                                        }
                                                },
                                        },
                                },
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_TRUE,
                                .TholdCapabilities = SAHPI_STC_INTERPRETED,
                                .ReadThold  = SAHPI_STM_LOW_MAJOR | SAHPI_STM_UP_MAJOR,
                                .FixedThold = SAHPI_STM_LOW_MAJOR | SAHPI_STM_UP_MAJOR,
                                /* Default HDW thresholds: Warning 1.32<>1.68 */
                        },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_UNSPECIFIED,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_CRIT |
                                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                                .DeassertEvents = SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_CRIT |
                                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        },
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .convert_snmpstr = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                .oid = ".1.3.6.1.4.1.2.3.51.2.22.1.5.5.1.11.x",
                                .threshold_oids = {
                                        .InterpretedThresholds = {
                                                .OidUpMajor  = ".1.3.6.1.4.1.2.3.51.2.22.1.5.6.1.16.x",
                                                .OidLowMajor = ".1.3.6.1.4.1.2.3.51.2.22.1.5.6.1.17.x",
                                        },
                                }
                        },
                        .event_array = {
                                {
                                        .event = "0A041C00", /* EN_IO_1_5V_WARNING_HI */
                                        .event_state = SAHPI_ES_UPPER_CRIT | SAHPI_ES_UPPER_MAJOR |
                                                       SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                },
                                {
                                        .event = "0A040C00", /* EN_IO_1_5V_WARNING_LOW */
                                        .event_state = SAHPI_ES_LOWER_CRIT | SAHPI_ES_LOWER_MAJOR |
                                                       SAHPI_ES_LOWER_MINOR,
                                        .recovery_state = SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_MINOR,
                                },
                                {
                                        .event = "08041400", /* EN_PFA_HI_FAULT_1_5V */
                                        .event_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UNSPECIFIED,
                                },
                                {
                                        .event = "08041800", /* EN_PFA_LO_FAULT_1_5V */
                                        .event_state = SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_MINOR,
                                        .recovery_state = SAHPI_ES_UNSPECIFIED,
                                },
                                {},
                        },
                },
                .comment = "Blade 1.5 volt sensor"
        },
        /* Blade's 2.5V voltage sensor */
        {
                .sensor = {
                        .Num = 10,
                        .Type = SAHPI_VOLTAGE,
                        .Category = SAHPI_EC_THRESHOLD,
                        .EventCtrl = SAHPI_SEC_GLOBAL_DISABLE,
                        .Events = SAHPI_ES_UNSPECIFIED |
                                  SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_CRIT |
                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_INTERPRETED,
                                .IsNumeric = SAHPI_TRUE,
                                .SignFormat = SAHPI_SDF_UNSIGNED,
                                .BaseUnits = SAHPI_SU_VOLTS,
                                .ModifierUnits = SAHPI_SU_UNSPECIFIED,
                                .ModifierUse = SAHPI_SMUU_NONE,
                                .FactorsStatic = SAHPI_TRUE,
                                .Factors = {
                                        .Linearization = SAHPI_SL_LINEAR,
                                },
                                .Percentage = SAHPI_FALSE,
                                .Range = {
                                        .Flags = SAHPI_SRF_MAX | SAHPI_SRF_MIN | SAHPI_SRF_NOMINAL,
                                        .Max = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 4.4,
                                                        }
                                                },
                                        },
                                        .Nominal = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 2.5,
                                                        }
                                                },
                                        },
                                        .Min = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 0,
                                                        }
                                                },
                                        },
                                },
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_TRUE,
                                .TholdCapabilities = SAHPI_STC_INTERPRETED,
                                .ReadThold  = SAHPI_STM_LOW_MAJOR | SAHPI_STM_UP_MAJOR,
                                .FixedThold = SAHPI_STM_LOW_MAJOR | SAHPI_STM_UP_MAJOR,
                                /* Default HDW thresholds: Warning 2.25<>2.75 */
                        },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_UNSPECIFIED,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_CRIT |
                                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                                .DeassertEvents = SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_CRIT |
                                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        },
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .convert_snmpstr = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                .oid = ".1.3.6.1.4.1.2.3.51.2.22.1.5.5.1.10.x",
                                .threshold_oids = {
                                        .InterpretedThresholds = {
                                                .OidUpMajor  = ".1.3.6.1.4.1.2.3.51.2.22.1.5.6.1.14.x",
                                                .OidLowMajor = ".1.3.6.1.4.1.2.3.51.2.22.1.5.6.1.15.x",
                                        },
                                },
                        },
                        .event_array = {
                                {
                                        .event = "0A031C00", /* EN_IO_2_5V_WARNING_HI */
                                        .event_state = SAHPI_ES_UPPER_CRIT | SAHPI_ES_UPPER_MAJOR |
                                                       SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                },
                                {
                                        .event = "0A030C00", /* EN_IO_2_5V_WARNING_LOW */
                                        .event_state = SAHPI_ES_LOWER_CRIT | SAHPI_ES_LOWER_MAJOR |
                                                       SAHPI_ES_LOWER_MINOR,
                                        .recovery_state = SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_MINOR,
                                },
                                {
                                        .event = "08031480", /* EN_PFA_HI_FAULT_2_5V */
                                        .event_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UNSPECIFIED,
                                },
                                {
                                        .event = "08031880", /* EN_PFA_LO_FAULT_2_5V */
                                        .event_state = SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_MINOR,
                                        .recovery_state = SAHPI_ES_UNSPECIFIED,
                                },
                                {},
                        },
                },
                .comment = "Blade 2.5 volt sensor"
        },
        /* Blade's 3.3V voltage sensor */
        {
                .sensor = {
                        .Num = 11,
                        .Type = SAHPI_VOLTAGE,
                        .Category = SAHPI_EC_THRESHOLD,
                        .EventCtrl = SAHPI_SEC_GLOBAL_DISABLE,
                        .Events = SAHPI_ES_UNSPECIFIED |
                                  SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_CRIT |
                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_INTERPRETED,
                                .IsNumeric = SAHPI_TRUE,
                                .SignFormat = SAHPI_SDF_UNSIGNED,
                                .BaseUnits = SAHPI_SU_VOLTS,
                                .ModifierUnits = SAHPI_SU_UNSPECIFIED,
                                .ModifierUse = SAHPI_SMUU_NONE,
                                .FactorsStatic = SAHPI_TRUE,
                                .Factors = {
                                        .Linearization = SAHPI_SL_LINEAR,
                                },
                                .Percentage = SAHPI_FALSE,
                                .Range = {
                                        .Flags = SAHPI_SRF_MAX | SAHPI_SRF_MIN | SAHPI_SRF_NOMINAL,
                                        .Max = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 4.4,
                                                        }
                                                },
                                        },
                                        .Nominal = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 3.3,
                                                        }
                                                },
                                        },
                                        .Min = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 0,
                                                        }
                                                },
                                        },
                                },
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_TRUE,
                                .TholdCapabilities = SAHPI_STC_INTERPRETED,
                                .ReadThold  = SAHPI_STM_LOW_MAJOR | SAHPI_STM_UP_MAJOR,
                                .FixedThold = SAHPI_STM_LOW_MAJOR | SAHPI_STM_UP_MAJOR,
                                /* Default HDW thresholds: Warning 2.97<>3.63 */
                        },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_UNSPECIFIED,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_CRIT |
                                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                                .DeassertEvents = SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_CRIT |
                                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        },
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .convert_snmpstr = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                .oid = ".1.3.6.1.4.1.2.3.51.2.22.1.5.5.1.7.x",
                                .threshold_oids = {
                                        .InterpretedThresholds = {
                                                .OidUpMajor  = ".1.3.6.1.4.1.2.3.51.2.22.1.5.6.1.8.x",
                                                .OidLowMajor = ".1.3.6.1.4.1.2.3.51.2.22.1.5.6.1.9.x",
                                        },
                                },
                        },
                        .event_array = {
                                {
                                        .event = "0A02DC00", /* EN_IO_3_3V_WARNING_HI */
                                        .event_state = SAHPI_ES_UPPER_CRIT | SAHPI_ES_UPPER_MAJOR |
                                                       SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                },
                                {
                                        .event = "0A02CC00", /* EN_IO_3_3V_WARNING_LOW */
                                        .event_state = SAHPI_ES_LOWER_CRIT | SAHPI_ES_LOWER_MAJOR |
                                                       SAHPI_ES_LOWER_MINOR,
                                        .recovery_state = SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_MINOR,
                                },
                                {
                                        .event = "08033480", /* EN_PFA_HI_FAULT_3_35V */
                                        .event_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UNSPECIFIED,
                                },
                                {
                                        .event = "08033880", /* EN_PFA_LO_FAULT_3_35V */
                                        .event_state = SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_MINOR,
                                        .recovery_state = SAHPI_ES_UNSPECIFIED,
                                },
                                {},
                        },
                },
                .comment = "Blade 3.3 volt sensor"
        },
        /* Blade's 5V voltage sensor */
        {
                .sensor = {
                        .Num = 12,
                        .Type = SAHPI_VOLTAGE,
                        .Category = SAHPI_EC_THRESHOLD,
                        .EventCtrl = SAHPI_SEC_GLOBAL_DISABLE,
                        .Events = SAHPI_ES_UNSPECIFIED |
                                  SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_CRIT |
                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_INTERPRETED,
                                .IsNumeric = SAHPI_TRUE,
                                .SignFormat = SAHPI_SDF_UNSIGNED,
                                .BaseUnits = SAHPI_SU_VOLTS,
                                .ModifierUnits = SAHPI_SU_UNSPECIFIED,
                                .ModifierUse = SAHPI_SMUU_NONE,
                                .FactorsStatic = SAHPI_TRUE,
                                .Factors = {
                                        .Linearization = SAHPI_SL_LINEAR,
                                },
                                .Percentage = SAHPI_FALSE,
                                .Range = {
                                        .Flags = SAHPI_SRF_MAX | SAHPI_SRF_MIN | SAHPI_SRF_NOMINAL,
                                        .Max = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 6.7,
                                                        }
                                                },
                                        },
                                        .Nominal = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 5,
                                                        }
                                                },
                                        },
                                        .Min = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 0,
                                                        }
                                                },
                                        },
                                },
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_TRUE,
                                .TholdCapabilities = SAHPI_STC_INTERPRETED,
                                .ReadThold  = SAHPI_STM_LOW_MAJOR | SAHPI_STM_UP_MAJOR,
                                .FixedThold = SAHPI_STM_LOW_MAJOR | SAHPI_STM_UP_MAJOR,
                                /* Default HDW thresholds: Warning 4.40<>5.50 */
                        },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_UNSPECIFIED,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_CRIT |
                                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                                .DeassertEvents = SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_CRIT |
                                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        },
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .convert_snmpstr = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                .oid = ".1.3.6.1.4.1.2.3.51.2.22.1.5.5.1.6.x",
                                .threshold_oids = {
                                        .InterpretedThresholds = {
                                                .OidUpMajor  = ".1.3.6.1.4.1.2.3.51.2.22.1.5.6.1.6.x",
                                                .OidLowMajor = ".1.3.6.1.4.1.2.3.51.2.22.1.5.6.1.7.x",
                                        },
                                },
                        },
                        .event_array = {
                                {
                                        .event = "0A035C00", /* EN_IO_5V_WARNING_HI */
                                        .event_state = SAHPI_ES_UPPER_CRIT | SAHPI_ES_UPPER_MAJOR |
                                                       SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                },
                                {
                                        .event = "0A034C00", /* EN_IO_5V_WARNING_LOW */
                                        .event_state = SAHPI_ES_LOWER_CRIT | SAHPI_ES_LOWER_MAJOR |
                                                       SAHPI_ES_LOWER_MINOR,
                                        .recovery_state = SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_MINOR,
                                },
                                {
                                        .event = "08035500", /* EN_PFA_HI_FAULT_5V */
                                        .event_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UNSPECIFIED,
                                },
                                {
                                        .event = "08035800", /* EN_PFA_LO_FAULT_5V */
                                        .event_state = SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_MINOR,
                                        .recovery_state = SAHPI_ES_UNSPECIFIED,
                                },
                                {},
                        },
                },
                .comment = "Blade 5 volt sensor"
        },
        /* Blade's 12V voltage sensor */
        {
                .sensor = {
                        .Num = 13,
                        .Type = SAHPI_VOLTAGE,
                        .Category = SAHPI_EC_THRESHOLD,
                        .EventCtrl = SAHPI_SEC_GLOBAL_DISABLE,
                        .Events = SAHPI_ES_UNSPECIFIED |
                                  SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_CRIT |
                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_INTERPRETED,
                                .IsNumeric = SAHPI_TRUE,
                                .SignFormat = SAHPI_SDF_UNSIGNED,
                                .BaseUnits = SAHPI_SU_VOLTS,
                                .ModifierUnits = SAHPI_SU_UNSPECIFIED,
                                .ModifierUse = SAHPI_SMUU_NONE,
                                .FactorsStatic = SAHPI_TRUE,
                                .Factors = {
                                        .Linearization = SAHPI_SL_LINEAR,
                                },
                                .Percentage = SAHPI_FALSE,
                                .Range = {
                                        .Flags = SAHPI_SRF_MAX | SAHPI_SRF_MIN | SAHPI_SRF_NOMINAL,
                                        .Max = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 16,
                                                        }
                                                },
                                        },
                                        .Nominal = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 12,
                                                        }
                                                },
                                        },
                                        .Min = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 0,
                                                        }
                                                },
                                        },
                                },
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_TRUE,
                                .TholdCapabilities = SAHPI_STC_INTERPRETED,
                                .ReadThold  = SAHPI_STM_LOW_MAJOR | SAHPI_STM_UP_MAJOR,
                                .FixedThold = SAHPI_STM_LOW_MAJOR | SAHPI_STM_UP_MAJOR,
                                /* Default HDW thresholds: Warning 10.8<>13.2 */
                        },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_UNSPECIFIED,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_CRIT |
                                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                                .DeassertEvents = SAHPI_ES_LOWER_MINOR | SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_CRIT |
                                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        },
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .convert_snmpstr = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                .oid = ".1.3.6.1.4.1.2.3.51.2.22.1.5.5.1.8.x",
                                .threshold_oids = {
                                        .InterpretedThresholds = {
                                                .OidUpMajor  = ".1.3.6.1.4.1.2.3.51.2.22.1.5.6.1.10.x",
                                                .OidLowMajor = ".1.3.6.1.4.1.2.3.51.2.22.1.5.6.1.11.x",
                                        },
                                },
                        },
                        .event_array = {
                                {
                                        .event = "0A037C00", /* EN_IO_12V_WARNING_HI */
                                        .event_state = SAHPI_ES_UPPER_CRIT | SAHPI_ES_UPPER_MAJOR |
                                                       SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                },
                                {
                                        .event = "0A036C00", /* EN_IO_12V_WARNING_LOW */
                                        .event_state = SAHPI_ES_LOWER_CRIT | SAHPI_ES_LOWER_MAJOR |
                                                       SAHPI_ES_LOWER_MINOR,
                                        .recovery_state = SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_MINOR,
                                },
                                {
                                        .event = "06037500", /* EN_PFA_HI_FAULT_12V_PLANAR */
                                        .event_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UNSPECIFIED,
                                },
                                {
                                        .event = "06037800", /* EN_PFA_LO_FAULT_12V_PLANAR */
                                        .event_state = SAHPI_ES_LOWER_MAJOR | SAHPI_ES_LOWER_MINOR,
                                        .recovery_state = SAHPI_ES_UNSPECIFIED,
                                },
                                {},
                        },
                },
                .comment = "Blade 12 volt sensor"
        },
        /* Blade's VRM 1 voltage sensor */
        {
                .sensor = {
                        .Num = 14,
                        .Type = SAHPI_VOLTAGE,
                        .Category = SAHPI_EC_THRESHOLD,
                        .EventCtrl = SAHPI_SEC_GLOBAL_DISABLE,
                        .Events = SAHPI_ES_UNSPECIFIED |
                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_INTERPRETED,
                                .IsNumeric = SAHPI_TRUE,
                                .SignFormat = SAHPI_SDF_UNSIGNED,
                                .BaseUnits = SAHPI_SU_VOLTS,
                                .ModifierUnits = SAHPI_SU_UNSPECIFIED,
                                .ModifierUse = SAHPI_SMUU_NONE,
                                .FactorsStatic = SAHPI_TRUE,
                                .Factors = {
                                        .Linearization = SAHPI_SL_LINEAR,
                                },
                                .Percentage = SAHPI_FALSE,
                                .Range = {
                                        .Flags = SAHPI_SRF_MAX | SAHPI_SRF_MIN,
                                        .Max = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 3.6,
                                                        }
                                                },
                                        },
                                        .Min = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 0,
                                                        }
                                                },
                                        },
                                },
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_TRUE,
                                .TholdCapabilities = SAHPI_STC_INTERPRETED,
                                .ReadThold  = 0, /* No readable thresholds */
                        },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_UNSPECIFIED,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                                .DeassertEvents = SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        },
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .convert_snmpstr = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                .oid = ".1.3.6.1.4.1.2.3.51.2.22.1.5.5.1.13.x",
                        },
                        .event_array = {
                                {
                                        .event = "04400481", /* EN_CUTOFF_HI_FAULT_VRM1 */
                                        .event_state = SAHPI_ES_UPPER_CRIT | SAHPI_ES_UPPER_MAJOR |
                                                       SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UNSPECIFIED,
                                },
                                {},
                        },
                },
                .comment = "Blade VRM 1 volt sensor"
        },
        /* Blade's global operational sensor */
        {
                .sensor = {
                        .Num = 16,
                        .Type = SAHPI_OPERATIONAL,
                        .Category = SAHPI_EC_AVAILABILITY,
                        .EventCtrl = SAHPI_SEC_GLOBAL_DISABLE,
                        .Events = SAHPI_ES_UNSPECIFIED | SAHPI_ES_RUNNING | SAHPI_ES_OFF_LINE |
                                  SAHPI_ES_DEGRADED | SAHPI_ES_INSTALL_ERROR,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_EVENT_STATE,
                                .IsNumeric = SAHPI_FALSE,
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_FALSE,
                        },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_UNSPECIFIED,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_DEGRADED | SAHPI_ES_OFF_LINE | SAHPI_ES_INSTALL_ERROR,
                                .DeassertEvents = SAHPI_ES_DEGRADED | SAHPI_ES_OFF_LINE | SAHPI_ES_INSTALL_ERROR,
                        },
                        .event_array = {
                                {
                                        .event = "0E00800x", /* EN_BLADE_x_COMM_FAIL */
                                        .event_state = SAHPI_ES_DEGRADED,
                                        .recovery_state = SAHPI_ES_RUNNING,
                                },
                                {
                                        .event = "0E00600x", /* EN_BLADE_x_CFG_FAIL */
                                        .event_state = SAHPI_ES_INSTALL_ERROR,
                                        .recovery_state = SAHPI_ES_RUNNING,
                                },
                                {
                                        .event = "06018000", /* EN_IO_BD_VOLTAGE_FAULT */
                                        .event_state = SAHPI_ES_DEGRADED,
                                        .recovery_state = SAHPI_ES_RUNNING,
                                },
                                {
                                        .event = "0601A000", /* EN_IO_BD_POWER_FAULT */
                                        .event_state = SAHPI_ES_DEGRADED,
                                        .recovery_state = SAHPI_ES_RUNNING,
                                },
                                {
                                        .event = "04018000", /* EN_CPU_BD_VOLTAGE_FAULT */
                                        .event_state = SAHPI_ES_DEGRADED,
                                        .recovery_state = SAHPI_ES_RUNNING,
                                },
                                {
                                        .event = "0000006F", /* EN_NC_VOLT */
                                        .event_state = SAHPI_ES_DEGRADED,
                                        .recovery_state = SAHPI_ES_RUNNING,
                                },
                                {
                                        .event = "00000077", /* EN_BOOT_FAIL */
                                        .event_state = SAHPI_ES_DEGRADED,
                                        .recovery_state = SAHPI_ES_RUNNING,
                                },
                                {
                                        .event = "00028001", /* EN_FAULT_SYS_POWER_GOOD */
                                        .event_state = SAHPI_ES_OFF_LINE,
                                        .recovery_state = SAHPI_ES_RUNNING,
                                },
                                {
                                        .event = "04428000", /* EN_FAULT_VRM_POWER_GOOD */
                                        .event_state = SAHPI_ES_OFF_LINE,
                                        .recovery_state = SAHPI_ES_RUNNING,
                                },
                                {
                                        .event = "0401A000", /* EN_CPU_BD_POWER_FAULT */
                                        .event_state = SAHPI_ES_DEGRADED,
                                        .recovery_state = SAHPI_ES_RUNNING,
                                },
                                {
                                        .event = "00028000", /* EN_FAULT_POWER_GOOD */
                                        .event_state = SAHPI_ES_DEGRADED,
                                        .recovery_state = SAHPI_ES_RUNNING,
                                },
                                {
                                        .event = "06800000", /* EN_FAULT_DASD */
                                        .event_state = SAHPI_ES_DEGRADED,
                                        .recovery_state = SAHPI_ES_RUNNING,
                                },
                                {},
                        },
                },
                .comment = "Blade global operational sensor"
        },

        {} /* Terminate array with a null element */
};

/******************************
 * Blade Expansion Card Sensors
 ******************************/

struct snmp_bc_sensor snmp_bc_blade_addin_sensors[] = {
        /* Blade's expansion card (DASD1) thermal sensor */
        {
                .sensor = {
                        .Num = 1,
                        .Type = SAHPI_TEMPERATURE,
                        .Category = SAHPI_EC_THRESHOLD,
                        .EventCtrl = SAHPI_SEC_GLOBAL_DISABLE,
                        .Events = SAHPI_ES_UNSPECIFIED |
                                  SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_INTERPRETED,
                                .IsNumeric = SAHPI_TRUE,
                                .SignFormat = SAHPI_SDF_UNSIGNED,
                                .BaseUnits = SAHPI_SU_DEGREES_C,
                                .ModifierUnits = SAHPI_SU_UNSPECIFIED,
                                .ModifierUse = SAHPI_SMUU_NONE,
                                .FactorsStatic = SAHPI_TRUE,
                                .Factors = {
                                        .Linearization = SAHPI_SL_LINEAR,
                                },
                                .Percentage = SAHPI_FALSE,
                                .Range = {
                                        .Flags = SAHPI_SRF_MAX | SAHPI_SRF_MIN,
                                        .Max = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 125,
                                                        }
                                                },
                                        },
                                        .Min = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 0,
                                                        }
                                                },
                                        },
                                },
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_TRUE,
                                .TholdCapabilities = SAHPI_STC_INTERPRETED,
                                .ReadThold  = SAHPI_STM_UP_MAJOR | SAHPI_STM_UP_CRIT,
                                .FixedThold = SAHPI_STM_UP_MAJOR | SAHPI_STM_UP_CRIT,
                        },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_UNSPECIFIED,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                                .DeassertEvents = SAHPI_ES_UPPER_MINOR | SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_CRIT,
                        },
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .convert_snmpstr = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                .oid = ".1.3.6.1.4.1.2.3.51.2.22.1.5.3.1.10.x",
                                .threshold_oids = {
                                        .InterpretedThresholds = {
                                                .OidUpCrit  = ".1.3.6.1.4.1.2.3.51.2.22.1.5.4.1.18.x",
                                                .OidUpMajor = ".1.3.6.1.4.1.2.3.51.2.22.1.5.4.1.19.x",
                                        },
                                },
                        },
                        .event_array = {
                                {
                                        .event = "0681C481", /* EN_CUTOFF_HI_OVER_TEMP_DASD1 */
                                        .event_state = SAHPI_ES_UPPER_CRIT | SAHPI_ES_UPPER_MAJOR |
                                                       SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                },
                                {
                                        .event = "0681D481", /* EN_PFA_HI_OVER_TEMP_DASD1 */
                                        .event_state = SAHPI_ES_UPPER_MAJOR | SAHPI_ES_UPPER_MINOR,
                                        .recovery_state = SAHPI_ES_UNSPECIFIED,
                                },
                                {},
                        },
                },
                .comment = "Blade expansion card (DASD1) thermal sensor"
        },
        {
                .sensor = {
                        .Num = 2,
                        .Type = SAHPI_VOLTAGE,
                        .Category = SAHPI_EC_SEVERITY,
                        .EventCtrl = SAHPI_SEC_GLOBAL_DISABLE,
                        .Events = SAHPI_ES_OK | SAHPI_ES_MAJOR_FROM_LESS,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_EVENT_STATE,
                                .IsNumeric = SAHPI_FALSE,
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_FALSE,
                        },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_OK,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_MAJOR_FROM_LESS,
                                .DeassertEvents = SAHPI_ES_MAJOR_FROM_LESS,
                        },
                        .event_array = {
                                {
                                        .event = "0E87A402", /* EN_BUST_1_8V_WARNING_HI */
                                        .event_state = SAHPI_ES_MAJOR_FROM_LESS,
                                        .recovery_state = SAHPI_ES_OK,
                                },
                                {
                                        .event = "0E87A802", /* EN_BUST_1_8V_WARNING_LOW */
                                        .event_state = SAHPI_ES_MAJOR_FROM_LESS,
                                        .recovery_state = SAHPI_ES_OK,
                                },
                                {
                                        .event = "0E830402", /* EN_BUST_2_5V_WARNING_HI */
                                        .event_state = SAHPI_ES_MAJOR_FROM_LESS,
                                        .recovery_state = SAHPI_ES_OK,
                                },
				{
                                        .event = "0E830802", /* EN_BUST_2_5V_WARNING_LOW */
                                        .event_state = SAHPI_ES_MAJOR_FROM_LESS,
                                        .recovery_state = SAHPI_ES_OK,
                                },
				{
					.event = "0E832402", /* EN_BUST_3_3V_WARNING_HI */
                                        .event_state = SAHPI_ES_MAJOR_FROM_LESS,
                                        .recovery_state = SAHPI_ES_OK,
                                },
				{
					.event = "0E832802", /* EN_BUST_3_3V_WARNING_LOW */
                                        .event_state = SAHPI_ES_MAJOR_FROM_LESS,
                                        .recovery_state = SAHPI_ES_OK,
                                },
				{
					.event = "0E834402", /* EN_BUST_5V_WARNING_HI */
                                        .event_state = SAHPI_ES_MAJOR_FROM_LESS,
                                        .recovery_state = SAHPI_ES_OK,
                                },
				{
					.event = "0E834802", /* EN_BUST_5V_WARNING_LOW */
                                        .event_state = SAHPI_ES_MAJOR_FROM_LESS,
                                        .recovery_state = SAHPI_ES_OK,
                                },
				{
					.event = "0E836402", /* EN_BUST_12V_WARNING_HI */
                                        .event_state = SAHPI_ES_MAJOR_FROM_LESS,
                                        .recovery_state = SAHPI_ES_OK,
                                },
				{
					.event = "0E836802", /* EN_BUST_12V_WARNING_LOW */
                                        .event_state = SAHPI_ES_MAJOR_FROM_LESS,
                                        .recovery_state = SAHPI_ES_OK,
                                },
				{
					.event = "0E83C402", /* EN_BUST_18V_WARNING_HI */
                                        .event_state = SAHPI_ES_MAJOR_FROM_LESS,
                                        .recovery_state = SAHPI_ES_OK,
                                },
				{
					.event = "0E83C802", /* EN_BUST_18V_WARNING_LOW */
                                        .event_state = SAHPI_ES_MAJOR_FROM_LESS,
                                        .recovery_state = SAHPI_ES_OK,
                                },
                                {},
                        },
                },
                .comment = "Blade expansion card voltage sensor"
        },

        {} /* Terminate array with a null element */
};

/***************************
 * Management Module Sensors
 ***************************/

struct snmp_bc_sensor snmp_bc_mgmnt_sensors[] = {

        {} /* Terminate array with a null element */
};

/********************
 * Media Tray Sensors
 ********************/

struct snmp_bc_sensor snmp_bc_mediatray_sensors[] = {
        /* Media Tray's global operational sensor */
        {
                .sensor = {
                        .Num = 1,
                        .Type = SAHPI_OPERATIONAL,
                        .Category = SAHPI_EC_AVAILABILITY,
                        .EventCtrl = SAHPI_SEC_GLOBAL_DISABLE,
                        .Events = SAHPI_ES_UNSPECIFIED | SAHPI_ES_RUNNING |
                                  SAHPI_ES_DEGRADED,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_EVENT_STATE,
                                .IsNumeric = SAHPI_FALSE,
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_FALSE,
                        },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_UNSPECIFIED,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_DEGRADED,
                                .DeassertEvents = SAHPI_ES_DEGRADED,
                        },
                        .event_array = {
                                {
                                        .event = "09020000", /* EN_FAULT_FP_R */
                                        .event_state = SAHPI_ES_DEGRADED,
                                        .recovery_state = SAHPI_ES_RUNNING,
                                },
                                {},
                        },
                },
                .comment = "Media Tray global operational sensor"
        },

        {} /* Terminate array with a null element */
};

/***********************
 * Blower Module Sensors
 ***********************/

struct snmp_bc_sensor snmp_bc_fan_sensors[] = {
        /* Blower fan speed */
        {
                .sensor = {
                        .Num = 1,
                        .Type = SAHPI_FAN,
                        .Category = SAHPI_EC_PRED_FAIL,
                        .EventCtrl = SAHPI_SEC_NO_EVENTS,
                        .Events = SAHPI_ES_PRED_FAILURE_ASSERT | SAHPI_ES_PRED_FAILURE_DEASSERT,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_INTERPRETED,
                                .IsNumeric = SAHPI_TRUE,
                                .SignFormat = SAHPI_SDF_UNSIGNED,
                                .BaseUnits = SAHPI_SU_RPM,
                                .ModifierUnits = SAHPI_SU_UNSPECIFIED,
                                .ModifierUse = SAHPI_SMUU_NONE,
                                .FactorsStatic = SAHPI_TRUE,
                                .Factors = {
                                        .Linearization = SAHPI_SL_LINEAR,
                                },
                                .Percentage = SAHPI_TRUE,
                                .Range = {
                                        .Flags = SAHPI_SRF_MAX | SAHPI_SRF_MIN,
                                        .Max = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 100,
                                                        }
                                                },
                                        },
                                        .Min = {
                                                .ValuesPresent = SAHPI_SRF_INTERPRETED,
                                                .Interpreted = {
                                                        .Type = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                                        .Value = {
                                                                .SensorFloat32 = 0,
                                                        }
                                                },
                                        },
                                },
                        },
                         .ThresholdDefn = {
                                .IsThreshold = SAHPI_FALSE
                        },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_UNSPECIFIED,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_PRED_FAILURE_ASSERT,
                                .DeassertEvents = SAHPI_ES_PRED_FAILURE_ASSERT,
                        },
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .convert_snmpstr = SAHPI_SENSOR_INTERPRETED_TYPE_FLOAT32,
                                .oid = ".1.3.6.1.4.1.2.3.51.2.2.3.x.0",
                        },
                        .event_array = {
                                {
                                        .event = "000A600x", /* EN_FAN1_PFA */
                                        .event_state = SAHPI_ES_PRED_FAILURE_ASSERT,
                                        .recovery_state = SAHPI_ES_PRED_FAILURE_DEASSERT,
                                },
                                {},
                        },
                },
                .comment = "Blower fan speed - percent of maximum RPM"
        },
        /* Blower's global operational sensor */
        {
                .sensor = {
                        .Num = 2,
                        .Type = SAHPI_OPERATIONAL,
                        .Category = SAHPI_EC_AVAILABILITY,
                        .EventCtrl = SAHPI_SEC_GLOBAL_DISABLE,
                        .Events = SAHPI_ES_UNSPECIFIED | SAHPI_ES_RUNNING |
                                  SAHPI_ES_OFF_LINE,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_EVENT_STATE,
                                .IsNumeric = SAHPI_FALSE,
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_FALSE,
                        },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_UNSPECIFIED,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_OFF_LINE,
                                .DeassertEvents = SAHPI_ES_OFF_LINE,
                        },
                        .event_array = {
                                {
                                        .event = "0002680x", /* EN_FAN1_SPEED */
                                        .event_state = SAHPI_ES_OFF_LINE,
                                        .recovery_state = SAHPI_ES_RUNNING,
                                },
                                {
                                        .event = "0A02600x", /* EN_FAULT_FAN1 */
                                        .event_state = SAHPI_ES_OFF_LINE,
                                        .recovery_state = SAHPI_ES_RUNNING,
                                },
                                {},
                        },
                },
                .comment = "Blower global operational sensor"
        },

        {} /* Terminate array with a null element */
};

/***************
 * Power Sensors
 ***************/

struct snmp_bc_sensor snmp_bc_power_sensors[] = {
        /* Power's over temperature sensor */
        {
                .sensor = {
                        .Num = 1,
                        .Type = SAHPI_TEMPERATURE,
                        .Category = SAHPI_EC_SEVERITY,
                        .EventCtrl = SAHPI_SEC_GLOBAL_DISABLE,
                        .Events = SAHPI_ES_OK | SAHPI_ES_MAJOR_FROM_LESS | SAHPI_ES_CRITICAL,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_EVENT_STATE,
                                .IsNumeric = SAHPI_FALSE,
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_FALSE,
                        },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_OK,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_MAJOR_FROM_LESS | SAHPI_ES_CRITICAL,
                                .DeassertEvents = SAHPI_ES_MAJOR_FROM_LESS | SAHPI_ES_CRITICAL,
                        },
                        .event_array = {
                                {
                                        .event = "0821C08x", /* EN_FAULT_PSx_OVR_TEMP */
                                        .event_state = SAHPI_ES_CRITICAL,
                                        .recovery_state = SAHPI_ES_MAJOR_FROM_LESS,
                                },
                                {
                                        .event = "0821C00x", /* EN_FAULT_PS1_TEMP_WARN */
                                        .event_state = SAHPI_ES_MAJOR_FROM_LESS,
                                        .recovery_state = SAHPI_ES_OK,
                                },
                                {},
                        },
                },
                .comment = "Power over temperature sensor"
        },
        /* Power's global operational sensor */
        {
                .sensor = {
                        .Num = 2,
                        .Type = SAHPI_OPERATIONAL,
                        .Category = SAHPI_EC_AVAILABILITY,
                        .EventCtrl = SAHPI_SEC_GLOBAL_DISABLE,
                        .Events = SAHPI_ES_UNSPECIFIED | SAHPI_ES_RUNNING | SAHPI_ES_OFF_LINE,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_EVENT_STATE,
                                .IsNumeric = SAHPI_FALSE,
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_FALSE,
                        },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_UNSPECIFIED,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_OFF_LINE,
                                .DeassertEvents = SAHPI_ES_OFF_LINE,
                        },
                        .event_array = {
                                {
                                        .event = "0820000x", /* EN_FAULT_PSx */
                                        .event_state = SAHPI_ES_OFF_LINE,
                                        .recovery_state = SAHPI_ES_RUNNING,
                                },
                                {
                                        .event = "0823600x", /* EN_FAULT_PSx_12V_OVR_CUR */
                                        .event_state = SAHPI_ES_OFF_LINE,
                                        .recovery_state = SAHPI_ES_RUNNING,
                                },
                                {
                                        .event = "0821A00x", /* EN_FAULT_PSx_CUR_FAIL */
                                        .event_state = SAHPI_ES_OFF_LINE,
                                        .recovery_state = SAHPI_ES_RUNNING,
                                },
                                {
                                        .event = "0802800x", /* EN_FAULT_PSx_DC_GOOD */
                                        .event_state = SAHPI_ES_OFF_LINE,
                                        .recovery_state = SAHPI_ES_RUNNING,
                                },
                                {
                                        .event = "0823648x", /* EN_FAULT_PSx_12V_OVER */
                                        .event_state = SAHPI_ES_OFF_LINE,
                                        .recovery_state = SAHPI_ES_RUNNING,
                                },
                                {
                                        .event = "0823680x", /* EN_FAULT_PSx_12V_UNDER */
                                        .event_state = SAHPI_ES_OFF_LINE,
                                        .recovery_state = SAHPI_ES_RUNNING,
                                },
                                {
                                        .event = "0818000x", /* EN_FAULT_PSx_EPOW */
                                        .event_state = SAHPI_ES_OFF_LINE,
                                        .recovery_state = SAHPI_ES_RUNNING,
                                },
                                {},
                        },
                },
                .comment = "Power global operational sensor"
        },
        {} /* Terminate array with a null element */
};

/****************
 * Switch Sensors
 ****************/

struct snmp_bc_sensor snmp_bc_switch_sensors[] = {
        /* Switch's over temperature sensor */
        {
                .sensor = {
                        .Num = 1,
                        .Type = SAHPI_TEMPERATURE,
                        .Category = SAHPI_EC_SEVERITY,
                        .EventCtrl = SAHPI_SEC_GLOBAL_DISABLE,
                        .Events = SAHPI_ES_OK | SAHPI_ES_MAJOR_FROM_LESS | SAHPI_ES_CRITICAL,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_EVENT_STATE,
                                .IsNumeric = SAHPI_FALSE,
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_FALSE,
                        },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_OK,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_MAJOR_FROM_LESS | SAHPI_ES_CRITICAL,
                                .DeassertEvents = SAHPI_ES_MAJOR_FROM_LESS | SAHPI_ES_CRITICAL,
                        },
                        .event_array = {
                                {
                                        .event = "0EA1C40x", /* EN_OVER_TEMP_SWITCH_x */
                                        .event_state = SAHPI_ES_CRITICAL,
                                        .recovery_state = SAHPI_ES_MAJOR_FROM_LESS,
                                },
                                {
                                        .event = "0EA1D40x", /* EN_OVER_TEMP_WARN_SWITCH_x */
                                        .event_state = SAHPI_ES_MAJOR_FROM_LESS,
                                        .recovery_state = SAHPI_ES_OK,
                                },
                                {},
                        },
                },
                .comment = "Switch over temperature sensor"
        },
        /* Switch's global operational sensor */
        {
                .sensor = {
                        .Num = 2,
                        .Type = SAHPI_OPERATIONAL,
                        .Category = SAHPI_EC_AVAILABILITY,
                        .EventCtrl = SAHPI_SEC_GLOBAL_DISABLE,
                        .Events = SAHPI_ES_UNSPECIFIED | SAHPI_ES_RUNNING |
                                  SAHPI_ES_DEGRADED | SAHPI_ES_INSTALL_ERROR,
                        .Ignore = SAHPI_FALSE,
                        .DataFormat = {
                                .ReadingFormats = SAHPI_SRF_EVENT_STATE,
                                .IsNumeric = SAHPI_FALSE,
                        },
                        .ThresholdDefn = {
                                .IsThreshold = SAHPI_FALSE,
                        },
                        .Oem = 0
                },
                .bc_sensor_info = {
                        .cur_state = SAHPI_ES_UNSPECIFIED,
                        .sensor_evt_enablement = {
                                .SensorStatus = SAHPI_SENSTAT_EVENTS_ENABLED,
                                .AssertEvents   = SAHPI_ES_DEGRADED | SAHPI_ES_INSTALL_ERROR,
                                .DeassertEvents = SAHPI_ES_DEGRADED | SAHPI_ES_INSTALL_ERROR,
                        },
                        .event_array = {
                                {
                                        .event = "0EA0C00x", /* EN_SWITCH_x_CFG_ERROR */
                                        .event_state = SAHPI_ES_INSTALL_ERROR,
                                        .recovery_state = SAHPI_ES_RUNNING,
                                },
                                {
                                        .event = "0EA0E00x", /* EN_SWITCH_x_POST_ERROR */
                                        .event_state = SAHPI_ES_INSTALL_ERROR,
                                        .recovery_state = SAHPI_ES_RUNNING,
                                },
                                {
                                        .event = "0EA0D00x", /* EN_SWITCH_x_POST_TIMEOUT */
                                        .event_state = SAHPI_ES_INSTALL_ERROR,
                                        .recovery_state = SAHPI_ES_RUNNING,
                                },
                                {
                                        .event = "0EA1A40x", /* EN_OVER_CURRENT_SWITCH_x */
                                        .event_state = SAHPI_ES_DEGRADED,
                                        .recovery_state = SAHPI_ES_RUNNING,
                                },
                                {},
                        },
                },
                .comment = "Switch global operational sensor"
        },

        {} /* Terminate array with a null element */
};

/*************************************************************************
 *                   Control Definitions
 *************************************************************************/

/******************
 * Chassis Controls
 ******************/

struct snmp_bc_control snmp_bc_chassis_controls[] = {

        /* Front Panel Information R/W LED */
        {
                .control = {
                        .Num = 1,
                        .Ignore = SAHPI_FALSE,
                        .OutputType = SAHPI_CTRL_LED,
                        .Type = SAHPI_CTRL_TYPE_DIGITAL,
                        .TypeUnion.Digital.Default = SAHPI_CTRL_STATE_OFF,
                        .Oem = 0
                },
                .bc_control_info = {
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .oid = ".1.3.6.1.4.1.2.3.51.2.2.8.1.2.0",
                                .digitalmap[0] = 0, /* Off */
                                .digitalmap[1] = 1, /* On */
                                .digitalmap[2] = -1, /* Not applicable */
                                .digitalmap[3] = -1, /* Not applicable */
                                .digitalmap[4] = -1, /* Not applicable */
                        },
                },
                .comment = "Front Panel LED - Information."
        },
        /* Front Panel Identify R/W LED */
        {
                .control = {
                        .Num = 2,
                        .Ignore = SAHPI_FALSE,
                        .OutputType = SAHPI_CTRL_LED,
                        .Type = SAHPI_CTRL_TYPE_DIGITAL,
                        .TypeUnion.Digital.Default = SAHPI_CTRL_STATE_OFF,
                        .Oem = 0
                },
                .bc_control_info = {
                        .mib = {
                                .not_avail_indicator_num = 3,
                                .write_only = 0,
                                .oid = ".1.3.6.1.4.1.2.3.51.2.2.8.1.4.0",
                                .digitalmap[0] = 0, /* Off */
                                .digitalmap[1] = 1, /* On */
                                .digitalmap[2] = -1, /* Not applicable */
                                .digitalmap[3] = 2, /* Blinking */
                                .digitalmap[4] = -1, /* Not applicable */
                        },
                },
                .comment = "Front Panel LED - Identify."
        },
        {} /* Terminate array with a null element */
};

/****************
 * Blade Controls
 ****************/
#define LAST_COMMON_BLADE_CONTROL_NUM 2

struct snmp_bc_control snmp_bc_blade_controls[] = {

        /* Blade Information R/W LED */
        {
                .control = {
                        .Num = 1,
                        .Ignore = SAHPI_FALSE,
                        .OutputType = SAHPI_CTRL_LED,
                        .Type = SAHPI_CTRL_TYPE_DIGITAL,
                        .TypeUnion.Digital.Default = SAHPI_CTRL_STATE_OFF,
                        .Oem = 0
                },
                .bc_control_info = {
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .oid = ".1.3.6.1.4.1.2.3.51.2.2.8.2.1.1.8.x",
                                .digitalmap[0] = 0, /* Off */
                                .digitalmap[1] = 1, /* On */
                                .digitalmap[2] = -1, /* Not applicable */
                                .digitalmap[3] = -1, /* Not applicable */
                                .digitalmap[4] = -1, /* Not applicable */
                        },
                },
                .comment = "Blade LED - Information."
        },
        /* Blade Identify R/W LED */
        {
                .control = {
                        .Num = LAST_COMMON_BLADE_CONTROL_NUM,
                        .Ignore = SAHPI_FALSE,
                        .OutputType = SAHPI_CTRL_LED,
                        .Type = SAHPI_CTRL_TYPE_DIGITAL,
                        .TypeUnion.Digital.Default = SAHPI_CTRL_STATE_OFF,
                        .Oem = 0
                },
                .bc_control_info = {
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .oid = ".1.3.6.1.4.1.2.3.51.2.2.8.2.1.1.11.x",
                                .digitalmap[0] = 0, /* Off */
                                .digitalmap[1] = 1, /* On */
                                .digitalmap[2] = -1, /* Not applicable */
                                .digitalmap[3] = 2, /* Blinking */
                                .digitalmap[4] = -1, /* Not applicable */
                        },
                },
                .comment = "Blade LED - Identify."
        },

        {} /* Terminate array with a null element */
};

struct snmp_bc_control snmp_bct_blade_controls[] = {
        /* Blade's number of restarts counter */
        {
                .control = {
                        .Num = LAST_COMMON_BLADE_CONTROL_NUM + 1,
                        .Ignore = SAHPI_FALSE,
                        .OutputType = SAHPI_CTRL_GENERIC,
                        .Type = SAHPI_CTRL_TYPE_DISCRETE,
                        .TypeUnion.Discrete.Default = 0,
                        .Oem = 0,
                },
                .bc_control_info = {
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .oid = ".1.3.6.1.4.1.2.3.51.2.22.1.10.1.1.x.3",
                        },
                },
                .comment = "Blade number of restarts counter"
        },

        {} /* Terminate array with a null element */
};

/***********************
 * Blade Add In Controls
 ***********************/

struct snmp_bc_control snmp_bc_blade_addin_controls[] = {

        {} /* Terminate array with a null element */
};

/****************************
 * Management Module Controls
 ****************************/

struct snmp_bc_control snmp_bc_mgmnt_controls[] = {

        {} /* Terminate array with a null element */
};

/*********************
 * Media Tray Controls
 *********************/

struct snmp_bc_control snmp_bc_mediatray_controls[] = {

        {} /* Terminate array with a null element */
};

/*****************
 * Blower Controls
 *****************/

struct snmp_bc_control snmp_bc_fan_controls[] = {

        {} /* Terminate array with a null element */
};

/****************
 * Power Controls
 ****************/

struct snmp_bc_control snmp_bc_power_controls[] = {

        {} /* Terminate array with a null element */
};

/************************
 * Switch Module Controls
 ************************/

struct snmp_bc_control snmp_bc_switch_controls[] = {

        {} /* Terminate array with a null element */
};

/*************************************************************************
 *                   Inventory Definitions
 *************************************************************************/

/*************
 * Chassis VPD
 *************/

struct snmp_bc_inventory snmp_bc_chassis_inventories[] = {
        {
                .inventory = {
                        .EirId = 1,
                        .Oem = 0,
                },
                .bc_inventory_info = {
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .inventory_type = SAHPI_INVENT_RECTYPE_CHASSIS_INFO,
                                .chassis_type = SAHPI_INVENT_CTYP_RACKMOUNT,
                                .oid = {
                                        .OidMfgDateTime = '\0',   /* Set to SAHPI_TIME_UNSPECIFIED */
                                        .OidManufacturer = ".1.3.6.1.4.1.2.3.51.2.2.21.1.1.5.0",
                                        .OidProductName = ".1.3.6.1.4.1.2.3.51.2.2.21.1.1.1.0",
                                        .OidProductVersion = ".1.3.6.1.4.1.2.3.51.2.2.21.1.1.6.0",
                                        .OidModelNumber = ".1.3.6.1.4.1.2.3.51.2.2.21.1.1.2.0",
                                        .OidSerialNumber = ".1.3.6.1.4.1.2.3.51.2.2.21.1.1.3.0",
                                        .OidPartNumber = ".1.3.6.1.4.1.2.3.51.2.2.21.1.1.7.0",
                                        .OidFileId = '\0',
                                        .OidAssetTag = '\0',
                                        /* UUID .1.3.6.1.4.1.2.3.51.2.2.21.1.1.4.0  */
                                }
                        },
                },
                .comment = "Chassis VPD",
        },

        {} /* Terminate array with a null element */
};

/*********
 * Fan VPD
 **********/

struct snmp_bc_inventory snmp_bc_fan_inventories[] = {

        {} /* Terminate array with a null element */
};

/***********************
 * Management Module VPD
 ***********************/

struct snmp_bc_inventory snmp_bc_mgmnt_inventories[] = {
        {
                .inventory = {
                        .EirId = 4,
                        .Oem = 0,
                },
                .bc_inventory_info = {
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .inventory_type = SAHPI_INVENT_RECTYPE_BOARD_INFO,
                                .chassis_type = SAHPI_INVENT_CTYP_RACKMOUNT,
                                .oid = {
                                        .OidMfgDateTime = '\0',   /* Set to SAHPI_TIME_UNSPECIFIED */
                                        .OidManufacturer = ".1.3.6.1.4.1.2.3.51.2.2.21.2.1.1.3.x",
                                        .OidProductName = '\0',
                                        .OidProductVersion = ".1.3.6.1.4.1.2.3.51.2.2.21.2.1.1.5.x",
                                        .OidModelNumber = '\0',
                                        .OidSerialNumber = '\0',
                                        .OidPartNumber = ".1.3.6.1.4.1.2.3.51.2.2.21.2.1.1.4.x",
                                        .OidFileId = '\0',
                                        .OidAssetTag = '\0',
                                        /* UUID .1.3.6.1.4.1.2.3.51.2.2.21.2.1.1.6.x */
                                }
                        },
                },
                .comment = "Management Module VPD",
        },

        {} /* Terminate array with a null element */
};

/*******************
 * Switch Module VPD
 *******************/

struct snmp_bc_inventory snmp_bc_switch_inventories[] = {
        {
                .inventory = {
                        .EirId = 5,
                        .Oem = 0,
                },
                .bc_inventory_info = {
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .inventory_type = SAHPI_INVENT_RECTYPE_BOARD_INFO,
                                .chassis_type = SAHPI_INVENT_CTYP_RACKMOUNT,
                                .oid = {
                                        .OidMfgDateTime = '\0',   /* Set to SAHPI_TIME_UNSPECIFIED */
                                        .OidManufacturer = ".1.3.6.1.4.1.2.3.51.2.2.21.6.1.1.3.x",
                                        .OidProductName = '\0',
                                        .OidProductVersion = ".1.3.6.1.4.1.2.3.51.2.2.21.6.1.1.5.x",
                                        .OidModelNumber = '\0',
                                        .OidSerialNumber = '\0',
                                        .OidPartNumber = ".1.3.6.1.4.1.2.3.51.2.2.21.6.1.1.4.x",
                                        .OidFileId = '\0',
                                        .OidAssetTag = '\0',
                                        /* UUID .1.3.6.1.4.1.2.3.51.2.2.21.6.1.1.8.x */
                                }
                        },
                },
                .comment = "Switch Module VPD",
        },

        {} /* Terminate array with a null element */
};

/************
 * Blade VPD
 ************/

struct snmp_bc_inventory snmp_bc_blade_inventories[] = {
        {
                .inventory = {
                        .EirId = 6,
                        .Oem = 0,
                },
                .bc_inventory_info = {
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .inventory_type = SAHPI_INVENT_RECTYPE_BOARD_INFO,
                                .chassis_type = SAHPI_INVENT_CTYP_RACKMOUNT,
                                .oid = {
                                        .OidMfgDateTime = '\0',   /* Set to SAHPI_TIME_UNSPECIFIED */
                                        .OidManufacturer = ".1.3.6.1.4.1.2.3.51.2.2.21.4.1.1.3.x",
                                        .OidProductName = ".1.3.6.1.4.1.2.3.51.2.2.21.4.1.1.7.x",
                                        .OidProductVersion = ".1.3.6.1.4.1.2.3.51.2.2.21.4.1.1.5.x",
                                        .OidModelNumber = '\0',
                                        .OidSerialNumber = ".1.3.6.1.4.1.2.3.51.2.2.21.4.1.1.6.x",
                                        .OidPartNumber = ".1.3.6.1.4.1.2.3.51.2.2.21.4.1.1.4.x",
                                        .OidFileId = '\0',
                                        .OidAssetTag = '\0',
                                        /* UUID .1.3.6.1.4.1.2.3.51.2.2.21.4.1.1.8.x */
                                }
                        },
                },
                .comment = "Blade VPD",
        },

        {} /* Terminate array with a null element */
};

/**************************
 * Blade Expansion Card VPD
 **************************/

struct snmp_bc_inventory snmp_bc_blade_addin_inventories[] = {

        {} /* Terminate array with a null element */
};

/****************
 * Media Tray VPD
 *****************/

struct snmp_bc_inventory snmp_bc_mediatray_inventories[] = {
        {
                .inventory = {
                        .EirId = 8,
                        .Oem = 0,
                },
                .bc_inventory_info = {
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .inventory_type = SAHPI_INVENT_RECTYPE_BOARD_INFO,
                                .chassis_type = SAHPI_INVENT_CTYP_RACKMOUNT,
                                .oid = {
                                        .OidMfgDateTime = '\0',   /* Set to SAHPI_TIME_UNSPECIFIED */
                                        .OidManufacturer = ".1.3.6.1.4.1.2.3.51.2.2.21.9.3.0",
                                        .OidProductName = '\0',
                                        .OidProductVersion = ".1.3.6.1.4.1.2.3.51.2.2.21.9.5.0",
                                        .OidModelNumber = '\0',
                                        .OidSerialNumber = '\0',
                                        .OidPartNumber = ".1.3.6.1.4.1.2.3.51.2.2.21.9.4.0",
                                        .OidFileId = '\0',
                                        .OidAssetTag = '\0',
                                        /* UUID .1.3.6.1.4.1.2.3.51.2.2.21.9.8.0 */
                                }
                        },
                },
                .comment = "Media Tray VPD",
        },

        {} /* Terminate array with a null element */
};

/*******************
 * Power Module VPD
 *******************/

struct snmp_bc_inventory snmp_bc_power_inventories[] = {
        {
                .inventory = {
                        .EirId = 9,
                        .Oem = 0,
                },
                .bc_inventory_info = {
                        .mib = {
                                .not_avail_indicator_num = 0,
                                .write_only = 0,
                                .inventory_type = SAHPI_INVENT_RECTYPE_BOARD_INFO,
                                .chassis_type = SAHPI_INVENT_CTYP_RACKMOUNT,
                                .oid = {
                                        .OidMfgDateTime = '\0',   /* Set to SAHPI_TIME_UNSPECIFIED */
                                        .OidManufacturer = ".1.3.6.1.4.1.2.3.51.2.2.21.8.1.1.3.x",
                                        .OidProductName = '\0',
                                        .OidProductVersion = ".1.3.6.1.4.1.2.3.51.2.2.21.8.1.1.5.x",
                                        .OidModelNumber = '\0',
                                        .OidSerialNumber = '\0',
                                        .OidPartNumber = ".1.3.6.1.4.1.2.3.51.2.2.21.8.1.1.4.x",
                                        .OidFileId = '\0',
                                        .OidAssetTag = '\0',
                                        /* UUID .1.3.6.1.4.1.2.3.51.2.2.21.8.1.1.8.x  */
                                }
                        },
                },
                .comment = "Power Module VPD",
        },

        {} /* Terminate array with a null element */
};
