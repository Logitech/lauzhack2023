using System;
using System.Collections.Generic;
using WebSocketSharp;
using Newtonsoft.Json;

namespace devmon_csharp
{
    class Device
    {
        public UInt32 unitId = 0;
        public string type = "";
        public string name = "";
        public bool isConnected = false;
        public bool hasWheel = false;
        public bool hasThumbWheel = false;
        public bool hasSpecialKeys = false;
    }

    class SpyConfig
    {
        public UInt32 unitId = 0;
        public bool spyButtons = false;
        public bool spyKeys = false;
        public bool spyPointer = false;
        public bool spyThumbWheel = false;
        public bool spyWheel = false;
    }

    class LogiDevMon
    {
        public static WebSocket ws;
        public static List<Device> devices;
        public static string devmonUrl = "ws://localhost:9876";


        public static void GetDevices(Func<List<Device>,int>callback)
        {
            devices = null;
            var msg = new { verb = "get", path = "devices" };
            var messageAsJsonString = JsonConvert.SerializeObject(msg);

            ws = new WebSocket(devmonUrl);

            ws.OnMessage += (sender, e) =>
            {
                devices = new List<Device>();

                Dictionary<string, object> objectData = JsonConvert.DeserializeObject<Dictionary<string, object>>(e.Data);
                if ((bool)objectData["success"])
                {
                    Newtonsoft.Json.Linq.JArray devicesArray = (Newtonsoft.Json.Linq.JArray)objectData["value"];

                    foreach (var device in devicesArray)
                    {
                        Device d = device.ToObject<Device>();
                        devices.Add(d);
                    }
                }

                ws.Close();

                callback(devices);
            };

            ws.Connect();

            ws.Send(messageAsJsonString);
        }

        public static void GetSpyConfig(UInt32 _unitId, Func<SpyConfig, int> callback)
        {
            var msg = new { verb = "get", path = "spyConfig", args = new {unitId = _unitId} };
            var jsonString = JsonConvert.SerializeObject(msg);

            ws = new WebSocket(devmonUrl);

            ws.OnMessage += (sender, e) =>
            {
                SpyConfig spyConfig = null;

                Dictionary<string, object> objectData = JsonConvert.DeserializeObject<Dictionary<string, object>>(e.Data);
                if ((bool)objectData["success"])
                {
                    Newtonsoft.Json.Linq.JObject o = (Newtonsoft.Json.Linq.JObject)objectData["value"];
                    spyConfig = o.ToObject<SpyConfig>();
                }
                ws.Close();
                callback(spyConfig);
            };

            ws.Connect();
            ws.Send(jsonString);
        }

        public static void SetSpyConfig(SpyConfig newSpyConfig)
        {
            var msg = new { verb = "set", path = "spyConfig", args = new { value = newSpyConfig } };
            var jsonString = JsonConvert.SerializeObject(msg);

            ws = new WebSocket(devmonUrl);

            ws.Connect();
            ws.Send(jsonString);
            ws.Close();
        }

        public static void ReadEvents(Func<object, WebSocket, int> callback)
        {
            ws = new WebSocket(devmonUrl);

            ws.OnMessage += (sender, e) =>
            {
                Dictionary<string, object> objectData = JsonConvert.DeserializeObject<Dictionary<string, object>>(e.Data);
                Newtonsoft.Json.Linq.JObject payload = null;
                if ((bool)objectData["success"])
                {
                    payload = (Newtonsoft.Json.Linq.JObject)objectData["value"];
                    
                }
                callback(payload, ws);
            };

            ws.Connect();
        }
    }
}
