var battery = require("@system.battery");
battery.BatterySOC({
    success: function(data) {
        console.log('success get battery Soc:' + data.batterySoc);
    },
    fail: function(data, code) {
        console.log('fail to get battery Soc code:' + code + ', data: ' + data);
    },
});

battery.ChargingStatus({
    success: function(data) {
        console.log('success get ChargingStatus:' + data.chargingStatus);
    },
    fail: function(data, code) {
        console.log('fail to get battery ChargingStatus code:' + code + ', data: ' + data);
    },
});

battery.HealthStatus({
    success: function(data) {
        console.log('success get battery HealthStatus:' + data.healthStatus);
    },
    fail: function(data, code) {
        console.log('fail to get battery HealthStatus code:' + code + ', data: ' + data);
    },
});

battery.PluggedType({
    success: function(data) {
        console.log('success get battery PluggedType:' + data.pluggedType);
    },
    fail: function(data, code) {
        console.log('fail to get battery PluggedType code:' + code + ', data: ' + data);
    },
});

battery.Voltage({
    success: function(data) {
        console.log('success get battery Voltage:' + data.voltage);
    },
    fail: function(data, code) {
        console.log('fail to get battery Voltage code:' + code + ', data: ' + data);
    },
});

battery.Technology({
    success: function(data) {
        console.log('success get battery Technology:' + data.technology);
    },
    fail: function(data, code) {
        console.log('fail to get battery Technology code:' + code + ', data: ' + data);
    },
});

battery.Temperature({
    success: function(data) {
        console.log('success get battery Temperature:' + data.temperature);
    },
    fail: function(data, code) {
        console.log('fail to get battery Temperature code:' + code + ', data: ' + data);
    },
});
