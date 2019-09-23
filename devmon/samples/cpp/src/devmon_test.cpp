#include <gmock/gmock.h>

#include <nlohmann/json.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

namespace logi
{
    namespace devmon
    {
        using json = nlohmann::json;

        using websocketpp_client = websocketpp::client<websocketpp::config::asio_client>;
        using connection_handle = websocketpp::connection_hdl;
        using connection_ptr = websocketpp_client::connection_ptr;
        using message_ptr = websocketpp_client::message_ptr;
        using value = websocketpp::frame::opcode::value;
        using error_code = websocketpp::lib::error_code;

        class devmon_test : public testing::Test {};
    }
}

using namespace logi::devmon;
using namespace std;
using namespace testing;

TEST_F(devmon_test, enumerate_devices)
{
    websocketpp_client client;

    // Initialize ASIO
    client.init_asio();

    auto on_fail = [&client](connection_handle handle)
    {
        printf("An error occurred\n");
        FAIL();
    };

    auto on_open = [&client](connection_handle handle)
    {
        printf("Connected to server\n");

        json message;
        message["verb"] = "get";
        message["path"] = "devices";

        client.send(handle, message.dump(), value::text);
    };

    auto on_close = [&client](connection_handle handle)
    {
        printf("Connection closed\n");
    };

    auto on_message = [&client](connection_handle handle, message_ptr message)
    {
        auto message_json = json::parse(message->get_payload());

        auto success = message_json["success"];
        ASSERT_TRUE(success.is_boolean());

        auto success_bool = success.get<bool>();
        ASSERT_TRUE(success_bool);

        auto verb = message_json["verb"];
        ASSERT_TRUE(verb.is_string());

        auto verb_string = verb.get<string>();
        ASSERT_EQ(verb_string, "get");

        auto path = message_json["path"];
        ASSERT_TRUE(path.is_string());

        auto path_string = path.get<string>();
        ASSERT_EQ(path_string, "devices");

        auto value = message_json["value"];
        ASSERT_TRUE(value.is_array());

        printf("Devices:\n%s\n", value.dump().c_str());

        client.close(handle, websocketpp::close::status::normal, "");
    };

    // Register handlers
    client.set_fail_handler(on_fail);
    client.set_open_handler(on_open);
    client.set_close_handler(on_close);
    client.set_message_handler(on_message);

    // Create websocket connection
    error_code error;
    connection_ptr connection = client.get_connection("ws://localhost:9876", error);

    if (error)
    {
        printf("%s", error.message().c_str());
        FAIL();
        return;
    }

    // Note that connect here only requests a connection.No network messages are
    // exchanged until the event loop starts running in the next line.
    client.connect(connection);

    // Start the ASIO io_service run loop
    // this will cause a single connection to be made to the server. c.run()
    // will exit when this connection is closed.
    client.run();
}

TEST_F(devmon_test, get_device_info)
{
    auto unit_id = 1953575442; // Replace with your device's unitId

    websocketpp_client client;

    // Initialize ASIO
    client.init_asio();

    auto on_fail = [&client](connection_handle handle)
    {
        printf("An error occurred\n");
        FAIL();
    };

    auto on_open = [&client, unit_id](connection_handle handle)
    {
        printf("Connected to server\n");

        json args;
        args["unitId"] = unit_id;

        json message;
        message["verb"] = "get";
        message["path"] = "device";
        message["args"] = args;

        client.send(handle, message.dump(), value::text);
    };

    auto on_close = [&client](connection_handle handle)
    {
        printf("Connection closed\n");
    };

    auto on_message = [&client](connection_handle handle, message_ptr message)
    {
        auto message_json = json::parse(message->get_payload());

        auto success = message_json["success"];
        ASSERT_TRUE(success.is_boolean());

        auto success_bool = success.get<bool>();
        ASSERT_TRUE(success_bool);

        auto verb = message_json["verb"];
        ASSERT_TRUE(verb.is_string());

        auto verb_string = verb.get<string>();
        ASSERT_EQ(verb_string, "get");

        auto path = message_json["path"];
        ASSERT_TRUE(path.is_string());

        auto path_string = path.get<string>();
        ASSERT_EQ(path_string, "device");

        auto value = message_json["value"];
        ASSERT_TRUE(value.is_object());

        printf("Device info:\n%s\n", value.dump().c_str());

        client.close(handle, websocketpp::close::status::normal, "");
    };

    // Register handlers
    client.set_fail_handler(on_fail);
    client.set_open_handler(on_open);
    client.set_close_handler(on_close);
    client.set_message_handler(on_message);

    // Create websocket connection
    error_code error;
    connection_ptr connection = client.get_connection("ws://localhost:9876", error);

    if (error)
    {
        printf("%s", error.message().c_str());
        FAIL();
        return;
    }

    // Note that connect here only requests a connection.No network messages are
    // exchanged until the event loop starts running in the next line.
    client.connect(connection);

    // Start the ASIO io_service run loop
    // this will cause a single connection to be made to the server. c.run()
    // will exit when this connection is closed.
    client.run();
}

TEST_F(devmon_test, get_spy_config)
{
    auto unit_id = 1953575442; // Replace with your device's unitId

    websocketpp_client client;

    // Initialize ASIO
    client.init_asio();

    auto on_fail = [&client](connection_handle handle)
    {
        printf("An error occurred\n");
        FAIL();
    };

    auto on_open = [&client, unit_id](connection_handle handle)
    {
        printf("Connected to server\n");

        json args;
        args["unitId"] = unit_id;

        json message;
        message["verb"] = "get";
        message["path"] = "spyConfig";
        message["args"] = args;

        client.send(handle, message.dump(), value::text);
    };

    auto on_close = [&client](connection_handle handle)
    {
        printf("Connection closed\n");
    };

    auto on_message = [&client](connection_handle handle, message_ptr message)
    {
        auto message_json = json::parse(message->get_payload());

        auto success = message_json["success"];
        ASSERT_TRUE(success.is_boolean());

        auto success_bool = success.get<bool>();
        ASSERT_TRUE(success_bool);

        auto verb = message_json["verb"];
        ASSERT_TRUE(verb.is_string());

        auto verb_string = verb.get<string>();
        ASSERT_EQ(verb_string, "get");

        auto path = message_json["path"];
        ASSERT_TRUE(path.is_string());

        auto path_string = path.get<string>();
        ASSERT_EQ(path_string, "spyConfig");

        auto value = message_json["value"];
        ASSERT_TRUE(value.is_object());

        printf("Spy config:\n%s\n", value.dump().c_str());

        client.close(handle, websocketpp::close::status::normal, "");
    };

    // Register handlers
    client.set_fail_handler(on_fail);
    client.set_open_handler(on_open);
    client.set_close_handler(on_close);
    client.set_message_handler(on_message);

    // Create websocket connection
    error_code error;
    connection_ptr connection = client.get_connection("ws://localhost:9876", error);

    if (error)
    {
        printf("%s", error.message().c_str());
        FAIL();
        return;
    }

    // Note that connect here only requests a connection.No network messages are
    // exchanged until the event loop starts running in the next line.
    client.connect(connection);

    // Start the ASIO io_service run loop
    // this will cause a single connection to be made to the server. c.run()
    // will exit when this connection is closed.
    client.run();
}

TEST_F(devmon_test, spy_device)
{
    auto unit_id = 1953575442; // Replace with your device's unitId

    websocketpp_client client;

    // Initialize ASIO
    client.init_asio();

    auto on_fail = [&client](connection_handle handle)
    {
        printf("An error occurred\n");
        FAIL();
    };
    
    auto on_open = [&client, unit_id](connection_handle handle)
    {
        printf("Connected to server\n");

        json value;
        value["unitId"] = unit_id;
        value["spyButtons"] = true;
        value["spyKeys"] = true;
        value["spyWheel"] = true;
        value["spyThumbWheel"] = true;
        value["spyPointer"] = true;

        json args;
        args["value"] = value;

        json message;
        message["verb"] = "set";
        message["path"] = "spyConfig";
        message["args"] = args;

        client.send(handle, message.dump(), value::text);
    };

    auto on_close = [&client](connection_handle handle)
    {
        printf("Connection closed\n");
    };

    auto on_message = [&client](connection_handle handle, message_ptr message)
    {
        auto message_json = json::parse(message->get_payload());

        auto success = message_json["success"];
        ASSERT_TRUE(success.is_boolean());

        auto success_bool = success.get<bool>();
        ASSERT_TRUE(success_bool);

        auto verb = message_json["verb"];
        ASSERT_TRUE(verb.is_string());

        auto verb_string = verb.get<string>();
        ASSERT_EQ(verb_string, "event");

        auto path = message_json["path"];
        ASSERT_TRUE(path.is_string());

        auto path_string = path.get<string>();

        auto value = message_json["value"];
        ASSERT_TRUE(value.is_object());

        printf("%s:%s\n", path_string.c_str(), value.dump().c_str());
    };

    // Register handlers
    client.set_fail_handler(on_fail);
    client.set_open_handler(on_open);
    client.set_close_handler(on_close);
    client.set_message_handler(on_message);

    // Create websocket connection
    error_code error;
    connection_ptr connection = client.get_connection("ws://localhost:9876", error);

    if (error)
    {
        printf("%s", error.message().c_str());
        FAIL();
        return;
    }

    // Note that connect here only requests a connection.No network messages are
    // exchanged until the event loop starts running in the next line.
    client.connect(connection);

    // End test after 10 seconds
    thread test_thread([&client, connection, unit_id]()
        {
            this_thread::sleep_for(chrono::seconds(10));

            // Stop spying
            json value;
            value["unitId"] = unit_id;
            value["spyButtons"] = false;
            value["spyKeys"] = false;
            value["spyWheel"] = false;
            value["spyThumbWheel"] = false;
            value["spyPointer"] = false;

            json args;
            args["value"] = value;

            json message;
            message["verb"] = "set";
            message["path"] = "spyConfig";
            message["args"] = args;

            client.send(connection->get_handle(), message.dump(), value::text);

            printf("Test ending\n");
            connection->close(websocketpp::close::status::normal, "");
        });

    // Start the ASIO io_service run loop
    // this will cause a single connection to be made to the server. c.run()
    // will exit when this connection is closed.
    client.run();
}

TEST_F(devmon_test, get_wheel_config)
{
    auto unit_id = 1953575442; // Replace with your device's unitId

    websocketpp_client client;

    // Initialize ASIO
    client.init_asio();

    auto on_fail = [&client](connection_handle handle)
    {
        printf("An error occurred\n");
        FAIL();
    };

    auto on_open = [&client, unit_id](connection_handle handle)
    {
        printf("Connected to server\n");

        json args;
        args["unitId"] = unit_id;

        json message;
        message["verb"] = "get";
        message["path"] = "wheelConfig";
        message["args"] = args;

        client.send(handle, message.dump(), value::text);
    };

    auto on_close = [&client](connection_handle handle)
    {
        printf("Connection closed\n");
    };

    auto on_message = [&client](connection_handle handle, message_ptr message)
    {
        auto message_json = json::parse(message->get_payload());

        auto success = message_json["success"];
        ASSERT_TRUE(success.is_boolean());

        auto success_bool = success.get<bool>();
        ASSERT_TRUE(success_bool);

        auto verb = message_json["verb"];
        ASSERT_TRUE(verb.is_string());

        auto verb_string = verb.get<string>();
        ASSERT_EQ(verb_string, "get");

        auto path = message_json["path"];
        ASSERT_TRUE(path.is_string());

        auto path_string = path.get<string>();
        ASSERT_EQ(path_string, "wheelConfig");

        auto value = message_json["value"];
        ASSERT_TRUE(value.is_object());

        printf("Wheel config:\n%s\n", value.dump().c_str());

        client.close(handle, websocketpp::close::status::normal, "");
    };

    // Register handlers
    client.set_fail_handler(on_fail);
    client.set_open_handler(on_open);
    client.set_close_handler(on_close);
    client.set_message_handler(on_message);

    // Create websocket connection
    error_code error;
    connection_ptr connection = client.get_connection("ws://localhost:9876", error);

    if (error)
    {
        printf("%s", error.message().c_str());
        FAIL();
        return;
    }

    // Note that connect here only requests a connection.No network messages are
    // exchanged until the event loop starts running in the next line.
    client.connect(connection);

    // Start the ASIO io_service run loop
    // this will cause a single connection to be made to the server. c.run()
    // will exit when this connection is closed.
    client.run();
}

TEST_F(devmon_test, get_wheel_events)
{
    auto unit_id = 1953575442; // Replace with your device's unitId

    websocketpp_client client;

    // Initialize ASIO
    client.init_asio();

    auto on_fail = [&client](connection_handle handle)
    {
        printf("An error occurred\n");
        FAIL();
    };

    auto on_open = [&client, unit_id](connection_handle handle)
    {
        printf("Connected to server\n");

        json value;
        value["unitId"] = unit_id;
        value["divert"] = true;
        value["hires"] = true;

        json args;
        args["value"] = value;

        json message;
        message["verb"] = "set";
        message["path"] = "wheelConfig";
        message["args"] = args;

        client.send(handle, message.dump(), value::text);
    };

    auto on_close = [&client](connection_handle handle)
    {
        printf("Connection closed\n");
    };

    auto on_message = [&client](connection_handle handle, message_ptr message)
    {
        auto message_json = json::parse(message->get_payload());

        auto success = message_json["success"];
        ASSERT_TRUE(success.is_boolean());

        auto success_bool = success.get<bool>();
        ASSERT_TRUE(success_bool);

        auto verb = message_json["verb"];
        ASSERT_TRUE(verb.is_string());

        auto verb_string = verb.get<string>();
        ASSERT_EQ(verb_string, "event");

        auto path = message_json["path"];
        ASSERT_TRUE(path.is_string());

        auto path_string = path.get<string>();
        ASSERT_EQ(path_string, "wheel");

        auto value = message_json["value"];
        ASSERT_TRUE(value.is_object());

        printf("%s\n", value.dump().c_str());
    };

    // Register handlers
    client.set_fail_handler(on_fail);
    client.set_open_handler(on_open);
    client.set_close_handler(on_close);
    client.set_message_handler(on_message);

    // Create websocket connection
    error_code error;
    connection_ptr connection = client.get_connection("ws://localhost:9876", error);

    if (error)
    {
        printf("%s", error.message().c_str());
        FAIL();
        return;
    }

    // Note that connect here only requests a connection.No network messages are
    // exchanged until the event loop starts running in the next line.
    client.connect(connection);

    // End test after 10 seconds
    thread test_thread([&client, connection, unit_id]()
        {
            this_thread::sleep_for(chrono::seconds(10));

            // Stop spying
            json value;
            value["unitId"] = unit_id;
            value["divert"] = false;
            value["hires"] = false;

            json args;
            args["value"] = value;

            json message;
            message["verb"] = "set";
            message["path"] = "wheelConfig";
            message["args"] = args;

            client.send(connection->get_handle(), message.dump(), value::text);

            printf("Test ending\n");
            connection->close(websocketpp::close::status::normal, "");
        });

    // Start the ASIO io_service run loop
    // this will cause a single connection to be made to the server. c.run()
    // will exit when this connection is closed.
    client.run();
}

TEST_F(devmon_test, get_thumb_wheel_config)
{
    auto unit_id = 1953575442; // Replace with your device's unitId

    websocketpp_client client;

    // Initialize ASIO
    client.init_asio();

    auto on_fail = [&client](connection_handle handle)
    {
        printf("An error occurred\n");
        FAIL();
    };

    auto on_open = [&client, unit_id](connection_handle handle)
    {
        printf("Connected to server\n");

        json args;
        args["unitId"] = unit_id;

        json message;
        message["verb"] = "get";
        message["path"] = "thumbWheelConfig";
        message["args"] = args;

        client.send(handle, message.dump(), value::text);
    };

    auto on_close = [&client](connection_handle handle)
    {
        printf("Connection closed\n");
    };

    auto on_message = [&client](connection_handle handle, message_ptr message)
    {
        auto message_json = json::parse(message->get_payload());

        auto success = message_json["success"];
        ASSERT_TRUE(success.is_boolean());

        auto success_bool = success.get<bool>();
        ASSERT_TRUE(success_bool);

        auto verb = message_json["verb"];
        ASSERT_TRUE(verb.is_string());

        auto verb_string = verb.get<string>();
        ASSERT_EQ(verb_string, "get");

        auto path = message_json["path"];
        ASSERT_TRUE(path.is_string());

        auto path_string = path.get<string>();
        ASSERT_EQ(path_string, "thumbWheelConfig");

        auto value = message_json["value"];
        ASSERT_TRUE(value.is_object());

        printf("Thumb Wheel config:\n%s\n", value.dump().c_str());

        client.close(handle, websocketpp::close::status::normal, "");
    };

    // Register handlers
    client.set_fail_handler(on_fail);
    client.set_open_handler(on_open);
    client.set_close_handler(on_close);
    client.set_message_handler(on_message);

    // Create websocket connection
    error_code error;
    connection_ptr connection = client.get_connection("ws://localhost:9876", error);

    if (error)
    {
        printf("%s", error.message().c_str());
        FAIL();
        return;
    }

    // Note that connect here only requests a connection.No network messages are
    // exchanged until the event loop starts running in the next line.
    client.connect(connection);

    // Start the ASIO io_service run loop
    // this will cause a single connection to be made to the server. c.run()
    // will exit when this connection is closed.
    client.run();
}

TEST_F(devmon_test, get_thumb_wheel_events)
{
    auto unit_id = 1953575442; // Replace with your device's unitId

    websocketpp_client client;

    // Initialize ASIO
    client.init_asio();

    auto on_fail = [&client](connection_handle handle)
    {
        printf("An error occurred\n");
        FAIL();
    };

    auto on_open = [&client, unit_id](connection_handle handle)
    {
        printf("Connected to server\n");

        json value;
        value["unitId"] = unit_id;
        value["divert"] = true;

        json args;
        args["value"] = value;

        json message;
        message["verb"] = "set";
        message["path"] = "thumbWheelConfig";
        message["args"] = args;

        client.send(handle, message.dump(), value::text);
    };

    auto on_close = [&client](connection_handle handle)
    {
        printf("Connection closed\n");
    };

    auto on_message = [&client](connection_handle handle, message_ptr message)
    {
        auto message_json = json::parse(message->get_payload());

        auto success = message_json["success"];
        ASSERT_TRUE(success.is_boolean());

        auto success_bool = success.get<bool>();
        ASSERT_TRUE(success_bool);

        auto verb = message_json["verb"];
        ASSERT_TRUE(verb.is_string());

        auto verb_string = verb.get<string>();
        ASSERT_EQ(verb_string, "event");

        auto path = message_json["path"];
        ASSERT_TRUE(path.is_string());

        auto path_string = path.get<string>();
        ASSERT_EQ(path_string, "thumbWheel");

        auto value = message_json["value"];
        ASSERT_TRUE(value.is_object());

        printf("%s\n", value.dump().c_str());
    };

    // Register handlers
    client.set_fail_handler(on_fail);
    client.set_open_handler(on_open);
    client.set_close_handler(on_close);
    client.set_message_handler(on_message);

    // Create websocket connection
    error_code error;
    connection_ptr connection = client.get_connection("ws://localhost:9876", error);

    if (error)
    {
        printf("%s", error.message().c_str());
        FAIL();
        return;
    }

    // Note that connect here only requests a connection.No network messages are
    // exchanged until the event loop starts running in the next line.
    client.connect(connection);

    // End test after 10 seconds
    thread test_thread([&client, connection, unit_id]()
        {
            this_thread::sleep_for(chrono::seconds(10));

            // Stop spying
            json value;
            value["unitId"] = unit_id;
            value["divert"] = false;

            json args;
            args["value"] = value;

            json message;
            message["verb"] = "set";
            message["path"] = "thumbWheelConfig";
            message["args"] = args;

            client.send(connection->get_handle(), message.dump(), value::text);

            printf("Test ending\n");
            connection->close(websocketpp::close::status::normal, "");
        });

    // Start the ASIO io_service run loop
    // this will cause a single connection to be made to the server. c.run()
    // will exit when this connection is closed.
    client.run();
}

TEST_F(devmon_test, get_special_keys_config)
{
    auto unit_id = 1953575442; // Replace with your device's unitId

    websocketpp_client client;

    // Initialize ASIO
    client.init_asio();

    auto on_fail = [&client](connection_handle handle)
    {
        printf("An error occurred\n");
        FAIL();
    };

    auto on_open = [&client, unit_id](connection_handle handle)
    {
        printf("Connected to server\n");

        json args;
        args["unitId"] = unit_id;

        json message;
        message["verb"] = "get";
        message["path"] = "specialKeys";
        message["args"] = args;

        client.send(handle, message.dump(), value::text);
    };

    auto on_close = [&client](connection_handle handle)
    {
        printf("Connection closed\n");
    };

    size_t nb_special_keys = 0;
    size_t special_keys_count = 0;

    auto on_message = [&client, &nb_special_keys, &special_keys_count, unit_id](connection_handle handle, message_ptr message)
    {
        auto message_json = json::parse(message->get_payload());

        auto success = message_json["success"];
        ASSERT_TRUE(success.is_boolean());

        auto success_bool = success.get<bool>();
        ASSERT_TRUE(success_bool);

        auto verb = message_json["verb"];
        ASSERT_TRUE(verb.is_string());

        auto verb_string = verb.get<string>();
        ASSERT_EQ(verb_string, "get");

        auto path = message_json["path"];
        ASSERT_TRUE(path.is_string());

        auto value = message_json["value"];

        auto path_string = path.get<string>();

        if (path_string == "specialKeys")
        {
            ASSERT_TRUE(value.is_array());
            printf("Special keys:\n%s\n", value.dump().c_str());

            nb_special_keys = value.size();
            special_keys_count = 0;

            for (auto& special_key : value)
            {
                auto control_id = special_key["controlId"];

                json args;
                args["unitId"] = unit_id;
                args["controlId"] = control_id;

                json message;
                message["verb"] = "get";
                message["path"] = "specialKeyConfig";
                message["args"] = args;

                client.send(handle, message.dump(), value::text);
            }
        }
        else if (path_string == "specialKeyConfig")
        {
            ASSERT_TRUE(value.is_object());
            printf("Special key config:\n%s\n", value.dump().c_str());

            special_keys_count++;

            if (nb_special_keys == special_keys_count)
            {
                client.close(handle, websocketpp::close::status::normal, "");
            }
        }
        else
        {
            FAIL();
        }
    };

    // Register handlers
    client.set_fail_handler(on_fail);
    client.set_open_handler(on_open);
    client.set_close_handler(on_close);
    client.set_message_handler(on_message);

    // Create websocket connection
    error_code error;
    connection_ptr connection = client.get_connection("ws://localhost:9876", error);

    if (error)
    {
        printf("%s", error.message().c_str());
        FAIL();
        return;
    }

    // Note that connect here only requests a connection.No network messages are
    // exchanged until the event loop starts running in the next line.
    client.connect(connection);

    // Start the ASIO io_service run loop
    // this will cause a single connection to be made to the server. c.run()
    // will exit when this connection is closed.
    client.run();
}

TEST_F(devmon_test, divert_special_key)
{
    auto unit_id = 1953575442; // Replace with your device's unitId
    auto control_id = 82; // Middle button

    websocketpp_client client;

    // Initialize ASIO
    client.init_asio();

    auto on_fail = [&client](connection_handle handle)
    {
        printf("An error occurred\n");
        FAIL();
    };

    auto on_open = [&client, unit_id, control_id](connection_handle handle)
    {
        printf("Connected to server\n");

        json value;
        value["unitId"] = unit_id;
        value["controlId"] = control_id;
        value["divert"] = true;

        json args;
        args["value"] = value;

        json message;
        message["verb"] = "set";
        message["path"] = "specialKeyConfig";
        message["args"] = args;

        client.send(handle, message.dump(), value::text);
    };

    auto on_close = [&client](connection_handle handle)
    {
        printf("Connection closed\n");
    };

    auto on_message = [&client](connection_handle handle, message_ptr message)
    {
        auto message_json = json::parse(message->get_payload());

        auto success = message_json["success"];
        ASSERT_TRUE(success.is_boolean());

        auto success_bool = success.get<bool>();
        ASSERT_TRUE(success_bool);

        auto verb = message_json["verb"];
        ASSERT_TRUE(verb.is_string());

        auto verb_string = verb.get<string>();
        ASSERT_EQ(verb_string, "event");

        auto path = message_json["path"];
        ASSERT_TRUE(path.is_string());

        auto path_string = path.get<string>();
        ASSERT_EQ(path_string, "divertedButtons");

        auto value = message_json["value"];
        ASSERT_TRUE(value.is_object());

        printf("%s\n", value.dump().c_str());
    };

    // Register handlers
    client.set_fail_handler(on_fail);
    client.set_open_handler(on_open);
    client.set_close_handler(on_close);
    client.set_message_handler(on_message);

    // Create websocket connection
    error_code error;
    connection_ptr connection = client.get_connection("ws://localhost:9876", error);

    if (error)
    {
        printf("%s", error.message().c_str());
        FAIL();
        return;
    }

    // Note that connect here only requests a connection.No network messages are
    // exchanged until the event loop starts running in the next line.
    client.connect(connection);

    // End test after 10 seconds
    thread test_thread([&client, connection, unit_id, control_id]()
        {
            this_thread::sleep_for(chrono::seconds(10));

            // Stop spying
            json value;
            value["unitId"] = unit_id;
            value["controlId"] = control_id;
            value["divert"] = false;

            json args;
            args["value"] = value;

            json message;
            message["verb"] = "set";
            message["path"] = "specialKeyConfig";
            message["args"] = args;

            client.send(connection->get_handle(), message.dump(), value::text);

            printf("Test ending\n");
            connection->close(websocketpp::close::status::normal, "");
        });

    // Start the ASIO io_service run loop
    // this will cause a single connection to be made to the server. c.run()
    // will exit when this connection is closed.
    client.run();
}

TEST_F(devmon_test, divert_pointer_when_pressing_middle_button)
{
    auto unit_id = 1953575442; // Replace with your device's unitId
    auto control_id = 82; // Middle button

    websocketpp_client client;

    // Initialize ASIO
    client.init_asio();

    auto on_fail = [&client](connection_handle handle)
    {
        printf("An error occurred\n");
        FAIL();
    };

    auto on_open = [&client, unit_id, control_id](connection_handle handle)
    {
        printf("Connected to server\n");

        json value;
        value["unitId"] = unit_id;
        value["controlId"] = control_id;
        value["divert"] = true;
        value["rawXY"] = true;

        json args;
        args["value"] = value;

        json message;
        message["verb"] = "set";
        message["path"] = "specialKeyConfig";
        message["args"] = args;

        client.send(handle, message.dump(), value::text);
    };

    auto on_close = [&client](connection_handle handle)
    {
        printf("Connection closed\n");
    };

    auto on_message = [&client](connection_handle handle, message_ptr message)
    {
        auto message_json = json::parse(message->get_payload());

        auto success = message_json["success"];
        ASSERT_TRUE(success.is_boolean());

        auto success_bool = success.get<bool>();
        ASSERT_TRUE(success_bool);

        auto verb = message_json["verb"];
        ASSERT_TRUE(verb.is_string());

        auto verb_string = verb.get<string>();
        ASSERT_EQ(verb_string, "event");

        auto path = message_json["path"];
        ASSERT_TRUE(path.is_string());

        auto path_string = path.get<string>();
        ASSERT_TRUE(path_string == "divertedButtons" || path_string == "divertedRawXY");

        auto value = message_json["value"];
        ASSERT_TRUE(value.is_object());

        printf("%s:%s\n", path_string.c_str(), value.dump().c_str());
    };

    // Register handlers
    client.set_fail_handler(on_fail);
    client.set_open_handler(on_open);
    client.set_close_handler(on_close);
    client.set_message_handler(on_message);

    // Create websocket connection
    error_code error;
    connection_ptr connection = client.get_connection("ws://localhost:9876", error);

    if (error)
    {
        printf("%s", error.message().c_str());
        FAIL();
        return;
    }

    // Note that connect here only requests a connection.No network messages are
    // exchanged until the event loop starts running in the next line.
    client.connect(connection);

    // End test after 10 seconds
    thread test_thread([&client, connection, unit_id, control_id]()
        {
            this_thread::sleep_for(chrono::seconds(10));

            // Stop spying
            json value;
            value["unitId"] = unit_id;
            value["controlId"] = control_id;
            value["divert"] = false;
            value["rawXY"] = false;

            json args;
            args["value"] = value;

            json message;
            message["verb"] = "set";
            message["path"] = "specialKeyConfig";
            message["args"] = args;

            client.send(connection->get_handle(), message.dump(), value::text);

            printf("Test ending\n");
            connection->close(websocketpp::close::status::normal, "");
        });

    // Start the ASIO io_service run loop
    // this will cause a single connection to be made to the server. c.run()
    // will exit when this connection is closed.
    client.run();
}

TEST_F(devmon_test, forcibly_divert_pointer)
{
    auto unit_id = 1953575442; // Replace with your device's unitId
    auto control_id = 215; // Virtual gesture button

    websocketpp_client client;

    // Initialize ASIO
    client.init_asio();

    auto on_fail = [&client](connection_handle handle)
    {
        printf("An error occurred\n");
        FAIL();
    };

    auto on_open = [&client, unit_id, control_id](connection_handle handle)
    {
        printf("Connected to server\n");

        json value;
        value["unitId"] = unit_id;
        value["controlId"] = control_id;
        value["divert"] = true;
        value["rawXY"] = true;
        value["forceRawXY"] = true;

        json args;
        args["value"] = value;

        json message;
        message["verb"] = "set";
        message["path"] = "specialKeyConfig";
        message["args"] = args;

        client.send(handle, message.dump(), value::text);
    };

    auto on_close = [&client](connection_handle handle)
    {
        printf("Connection closed\n");
    };

    auto on_message = [&client](connection_handle handle, message_ptr message)
    {
        auto message_json = json::parse(message->get_payload());

        auto success = message_json["success"];
        ASSERT_TRUE(success.is_boolean());

        auto success_bool = success.get<bool>();
        ASSERT_TRUE(success_bool);

        auto verb = message_json["verb"];
        ASSERT_TRUE(verb.is_string());

        auto verb_string = verb.get<string>();
        ASSERT_EQ(verb_string, "event");

        auto path = message_json["path"];
        ASSERT_TRUE(path.is_string());

        auto path_string = path.get<string>();
        ASSERT_TRUE(path_string == "divertedButtons" || path_string == "divertedRawXY");

        auto value = message_json["value"];
        ASSERT_TRUE(value.is_object());

        printf("%s:%s\n", path_string.c_str(), value.dump().c_str());
    };

    // Register handlers
    client.set_fail_handler(on_fail);
    client.set_open_handler(on_open);
    client.set_close_handler(on_close);
    client.set_message_handler(on_message);

    // Create websocket connection
    error_code error;
    connection_ptr connection = client.get_connection("ws://localhost:9876", error);

    if (error)
    {
        printf("%s", error.message().c_str());
        FAIL();
        return;
    }

    // Note that connect here only requests a connection.No network messages are
    // exchanged until the event loop starts running in the next line.
    client.connect(connection);

    // End test after 10 seconds
    thread test_thread([&client, connection, unit_id, control_id]()
        {
            this_thread::sleep_for(chrono::seconds(10));

            // Stop spying
            json value;
            value["unitId"] = unit_id;
            value["controlId"] = control_id;
            value["divert"] = false;
            value["rawXY"] = false;
            value["forceRawXY"] = false;

            json args;
            args["value"] = value;

            json message;
            message["verb"] = "set";
            message["path"] = "specialKeyConfig";
            message["args"] = args;

            client.send(connection->get_handle(), message.dump(), value::text);

            printf("Test ending\n");
            connection->close(websocketpp::close::status::normal, "");
        });

    // Start the ASIO io_service run loop
    // this will cause a single connection to be made to the server. c.run()
    // will exit when this connection is closed.
    client.run();
}
