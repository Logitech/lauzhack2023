# Developing Logitech Options+ plug-ins

## Installing the Options+ Software
To configure the end-to-end execution environment for Options+:

- Uninstall any existing version of Options+ from the target system.
- Copy the included **[features.cfg](./features.cfg)** file to the necessary locations on the target system.  On Windows, this file should be copied to the root directory of the drive to which Options+ will be installed.  On macOS, the file will need to be copied to ALL the following four locations:

    ``/Applications``

    ``/Library``

    ``/Users``

   ``/Users/<username>/Library/Application Support``

Run the installer for the appropriate target environment to install the Options+ software.  For Windows, this will be the logioptionsplus_installer_offline.exe file;  for macOS, the application bundle is archived in the logioptionsplus_installer_offline.Mac.zip file.
Navigate to the Application Settings page in Options+, and enable development mode for plug-ins.

## Creating a Plug-in Module
Plug-in modules are standalone executables or JavaScript applications that communicate with the Options+ plug-in manager using a WebSocket interface.

There is an [example plug-in module](./example%20plugin/) that illustrates the basics of plug-in development.  This plug-in will display the local weather in a new browser tab or window.  The plug-in has been implemented in JavaScript, and in C++ for Windows and Apple Silicon macOS.  

There is also a more detailed document, named [logi_plugin_sdk.pdf](./logi_plugin_sdk.pdf), that describes the plug-in SDK.

## Deploying a Plug-in Module

- Find the plug-ins directory for the target system.  

    On Windows, this will be the ``\Users\<username>\AppData\Local\Logi\PluginFramework\plugins`` directory on the boot drive.  

    On macOS, this will be ``/Users/<username>/Library/Application Support/Logi/PluginFramework/plugins``.

- Create a subdirectory within this directory for the plug-in, and copy the plug-in code and manifest file to this subdirectory.
- For JavaScript plug-ins only, start the JavaScript application manually using the node utility.
- Restart the plug-in manager.  This can be done by force-quitting the `logi_plugin_manager_agent` process from the Activity Monitor on macOS, or terminating the `Plugin Manager Agent` process from the Task Manager on Windows.

Note that this version of Options+ does not support hot module reloading or automatic updates.  Because of this, whenever a new version of a plug-in file or manifest file is deployed, the plug-in manager will need to be restarted.

Note also that any actions supported by the plug-in will not be visible in the Options+ application until Options+ is restarted.
