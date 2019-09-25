using System;
using System.Collections.Generic;
using System.Threading;
using WebSocketSharp;
using Newtonsoft.Json;

namespace devmon_csharp
{
    class Program
    {
        static int eventsCount = 50;
        static int keyboardIndex = -1;

        static int ListDevices(List<Device> devices)
        {
            Console.WriteLine("Devices List");
            int i = 0;
            foreach(Device device in devices)
            {
                Console.WriteLine(device.unitId + " " + device.type + ": " + device.name);
                if (device.type == "keyboard")
                {
                    keyboardIndex = i;
                }
                i++;
            }
            return 0;
        }

        static int ShowSpyConfig(SpyConfig sp)
        {
            if (sp != null)
            {
                Console.WriteLine(sp.unitId + ": buttons:" + sp.spyButtons + ", keys:" + sp.spyKeys + ", pointer:" + sp.spyPointer + ", thumbWheel:" + sp.spyThumbWheel +", wheel:"+ sp.spyWheel);
            }
            return 0;
        }
        
        static int ShowEvents(object payload, WebSocket ws)
        {
            string jsonString = JsonConvert.SerializeObject(payload);
            Console.WriteLine(eventsCount + ": " + jsonString);
            eventsCount--;

            if (eventsCount < 1)
            {
                ws.Close();

                Console.WriteLine("Stop spying keyboard keys");
                SpyConfig spyconfig = new SpyConfig
                {
                    unitId = LogiDevMon.devices[0].unitId,
                    spyKeys = false
                };

                LogiDevMon.SetSpyConfig(spyconfig);
            }
            return 0;
        }

        static void Main(string[] args)
        {
            LogiDevMon.GetDevices(ListDevices);

            Thread.Sleep(1500);

            Console.WriteLine();

            if (LogiDevMon.devices.Count > 0 && keyboardIndex != -1)
            {
                Console.WriteLine("SpyConfig for: " + LogiDevMon.devices[keyboardIndex].name);
                LogiDevMon.GetSpyConfig(LogiDevMon.devices[keyboardIndex].unitId, ShowSpyConfig);

                Thread.Sleep(1000);

                SpyConfig spyconfig = new SpyConfig
                {
                    unitId = LogiDevMon.devices[keyboardIndex].unitId,
                    spyKeys = true
                };

                Console.WriteLine("\nSpy keyboard keys");
                LogiDevMon.SetSpyConfig(spyconfig);
                Thread.Sleep(1000);
                LogiDevMon.GetSpyConfig(LogiDevMon.devices[keyboardIndex].unitId, ShowSpyConfig);
                Thread.Sleep(1000);

                Console.WriteLine("\nRead Key events");
                LogiDevMon.ReadEvents(ShowEvents);

            }
            else
            {
                Console.WriteLine("No keyboard detected, press any key to exit...");
            }

            Console.ReadKey(true);
        }
    }
}