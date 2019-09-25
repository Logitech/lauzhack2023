using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using WebSocketSharp;
using Newtonsoft.Json;
public class LogiDevMon : MonoBehaviour
{
    WebSocket ws = new WebSocket("ws://localhost:9876");
    string commandStr;
    bool first = true;
    // Start is called before the first frame update
    void Start()
    {
        Debug.Log("On Start");

        ws.OnMessage += (sender, e) =>
        {
            Debug.Log("Devmon server: " + e.Data);
            ws.Close();
        };

        ws.Connect();

        var command = new { verb = "get", path = "devices" };
        commandStr = JsonConvert.SerializeObject(command);
    }

    // Update is called once per frame
    void Update()
    {
        if (first)
        {
            Debug.Log("Sending: " + commandStr);
            ws.Send(commandStr);
            first = false;
        }
    }
}
