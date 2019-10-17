/********************************************************************/
            Corrections to the Turbo Debugger User's Guide


Chapter 17, "Turbo Debugger for Windows (TDW)"
----------------------------------------------
  - p. 282  The second paragraph on the page is no longer correct. The 
            method TDW uses to handle SVGA drivers has changed. You tell 
            TDW which driver to use by typing its name in the VideoDLL 
            entry in the TDW.INI file. See the README file for more 
            information on TDW.INI and video drivers.


Chapter 18, "Debugging a standard Windows Application"
-------------------------------------------------------
  - p. 312  Replace the statement "return DoWMCommand(wParam)" with
            "return DoWMCommand(wParam,hWnd)".

  - p. 315  The call to ReleaseDC isn't required and should be 
            deleted.


Appendix E, "Remote Debugging"
------------------------------
  The Windows initialization file WREMOTE.INI is no longer used by
  WREMOTE. Instead, WREMOTE looks in TDW.INI for its initialization
  information. When you run WRSETUP, it saves the same information to
  TDW.INI that it used to save to WREMOTE.INI. As was the case with 
  WREMOTE.INI, the remote configuration options are in the [WRemote] 
  section of TDW.INI.

  If you set up WREMOTE using a previous version of WRSETUP, you can 
  copy your old WREMOTE.INI settings to TDW.INI. Be sure to include the
  section header [WRemote].

  - p. 387  References to WREMOTE.INI should be changed to TDW.INI.
