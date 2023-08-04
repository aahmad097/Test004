# Test004 #

Persistence via Shell Extensions

---

# Into to Windows Shell #

The windows shell is the Graphical User Interface for the Windows Operating System, which includes the following:

- Desktop
- Start Menu
- Taskbar
- Etc.

---

# [Shell Development](https://learn.microsoft.com/en-us/previous-versions/windows/desktop/legacy/bb776778(v=vs.85)) #

```
"The Windows UI provides users with access to a wide variety of objects necessary to run applications and manage the operating system." 

- Some guy at microsoft
```

Includes but not limited to:

- implementing custom file formats
- implementing control panel items
- implementing in-process extensions
- Shell Extensibility (creating a data source)

We will be focusing on shell extensibility ... (Shell Extensions)

---

# [Shell Extensibility](https://learn.microsoft.com/en-us/previous-versions/windows/desktop/legacy/ff521728(v=vs.85)) #

- Extending the Desktop
- Using the search Protocol
- AutoRun and AutoPlay
- **[Extending Windows Explorer](https://learn.microsoft.com/en-us/previous-versions//ff514077(v=vs.85)?redirectedfrom=MSDN)**

---

# [Shell Extension Handlers](https://learn.microsoft.com/en-us/windows/win32/shell/handlers) # 

- Shell capabilities can be extended with registry entries and .ini files

- Shell Extension handlers impliment actions a shell can perform 
    - *example: Drop Handler - Called when an object is dragged over or dropped on a file* 

--- 

# Shell Extension Handler Examples (file type association) #

- Shortcut Menu Handler
- Data Handler
- Drop Handler
- Icon Handler 
- Property Sheet Hndler
- Thumbnail Image Handler
- Infotip Handler
- Metadata Handler

---

# Shell Extension Handler Examples (non file type association) #

- Column Handler (XP and earlier)
- Copy hook handler
- Drag and Drop handler
- Icon Overlay Handler
- Search Handler (XP and earlier)

---

# More on Handlers (Handlers++) # 

```
"Many Shell extension handlers are in-process Component Object Model (COM) objects. They must be assigned a GUID and registered as described in Registering Shell Extension Handlers."

- Probably the same dude from microsoft
```

- SO... all extensions must implement IUknown interface

---

# [Basic COM Primer 1](https://www.codeproject.com/Articles/633/Introduction-to-COM-What-It-Is-and-How-to-Use-It) #

- What is COM (Component Object Model)? 
    - method for sharing binary code across applications

- COM creates a binary standard (modules compiled in a specific structure) so that modules can be accessed from any programming language

--- 

# Basic COM Primer 2 #

- Interface? 
    - Group of functions called `methods`
    - Interface names start with _`I`_ as in `IUnknown`

- COClass? 
    - Component Object Class: contained in DLL / EXE
    - COClass impliments interfaces 
    - COM object is na instance of COClass in memory

- COM Server?
    - Binary containing one or more coclasses.

- GUID?
    - Globally Unique Identifier: Unique 128 bit number
    - each interface and coclass has a GUID
---

# Basic COM Primer 3 #

- Instances created using `CoCreateInstance` method
- Instances released using `Release` method defined in `IUnknown`

**IUnknown:**

   - AddRef() : increment reference count
   - Release() : decrement reference count
   - QueryInterface() : requests interface pointer from COM Object (used when coclass implements more than one interface)

---

# Back to Shell Extensions #

- When X action happens our Y dll gets loaded

- Handlers included in this project: 
    - IconOverlay Handler
    - IconHandler (file specific)
    - Drop Handler
    - Property Sheet Handler (file specific)
    - Thumbnail Image Handler (file specific)
    - Infotip Handler (file specific)
    - Copy Hook Handler  
    - Data Handler (file specific)

---

# [IconOverlay Handler](https://learn.microsoft.com/en-us/windows/win32/shell/how-to-implement-icon-overlay-handlers) #

- Interfaces: 
    - IUnknown
    - [IShellIconOverlayIdentifier](https://learn.microsoft.com/en-us/windows/win32/api/shobjidl_core/nn-shobjidl_core-ishelliconoverlayidentifier)
        - GetOverlayInfo: Provides the location of the icon overlay's bitmap.
        - GetPriority: Specifies the priority of an icon overlay.
        - IsMemberOf: Specifies whether an icon overlay should be added to a Shell object's icon.

---
# [IconHandler](https://learn.microsoft.com/en-us/windows/win32/shell/how-to-create-icon-handlers) # 

- Interfaces:
    - IUnknown 
    - [IPersistFile](https://learn.microsoft.com/en-us/windows/win32/api/objidl/nn-objidl-ipersistfile)
        - GetCurFile: Retrieves the current name of the file associated with the object. If there is no current working file, this method retrieves the default save prompt for the object.
        - IsDirty: Determines whether an object has changed since it was last saved to its current file.
        - Load: Opens the specified file and initializes an object from the file contents.
        - Save: Saves a copy of the object to the specified file.
        - SaveCompleted: Notifies the object that it can write to its file.
    - [IExtractIcon](https://learn.microsoft.com/en-us/windows/win32/api/shlobj_core/nn-shlobj_core-iextracticona)
        - Extract: Extracts an icon image from the specified location
        - GetIconLocation: Gets the location and index of an icon.

- [Very thorough tutorial on writing Icon Handlers. Shoutout to Pavel!](https://scorpiosoftware.net/2021/12/11/icon-handler-with-atl/)

---

# [Drop Handler](https://learn.microsoft.com/en-us/windows/win32/shell/how-to-create-drop-handlers) #

- Interfaces:
    - IUnknown 
    - [IPersistFile](https://learn.microsoft.com/en-us/windows/win32/api/objidl/nn-objidl-ipersistfile)
        - GetCurFile: Retrieves the current name of the file associated with the object. If there is no current working file, this method retrieves the default save prompt for the object.
        - IsDirty: Determines whether an object has changed since it was last saved to its current file.
        - Load: Opens the specified file and initializes an object from the file contents.
        - Save: Saves a copy of the object to the specified file.
        - SaveCompleted: Notifies the object that it can write to its file.
    - [IDropTarget](https://learn.microsoft.com/en-us/windows/win32/api/oleidl/nn-oleidl-idroptarget)
        - DragEnter: Indicates whether a drop can be accepted, and, if so, the effect of the drop.
        - DragLeave: Removes target feedback and releases the data object.
        - DragOver: Provides target feedback to the user and communicates the drop's effect to the DoDragDrop function so it can communicate the effect of the drop back to the source.
        - Drop: Incorporates the source data into the target window, removes target feedback, and releases the data object.
--- 

# [Property Sheet Handler (file specific)](https://learn.microsoft.com/en-us/windows/win32/shell/propsheet-handlers) #

- Interfaces: 
    - IUnknown
    - [IShellExtInit](https://learn.microsoft.com/en-us/windows/win32/api/shobjidl_core/nn-shobjidl_core-ishellextinit)
        - Initialize: Initializes a property sheet extension, shortcut menu extension, or drag-and-drop handler.
    - [IShellPropSheetExt](https://learn.microsoft.com/en-us/windows/win32/api/shobjidl_core/nn-shobjidl_core-ishellpropsheetext)
        - AddPages: Adds one or more pages to a property sheet that the Shell displays for a file object. The Shell calls this method for each property sheet handler registered to the file type.
        - ReplacePage: Replaces a page in a property sheet for a Control Panel object.

---

# [Thumbnail Image Handler (file specific)](https://learn.microsoft.com/en-us/windows/win32/api/thumbcache/nn-thumbcache-ithumbnailprovider) #
    
- Interfaces
    - IUnknown
    - [IThumbnailProvider](https://learn.microsoft.com/en-us/windows/win32/api/thumbcache/nn-thumbcache-ithumbnailprovider)
        - GetThumbnail: Gets a thumbnail image and alpha type.

---

# [Infotip Handler (file specific)](https://learn.microsoft.com/en-us/windows/win32/api/shlobj_core/nn-shlobj_core-iqueryinfo) #

- Interfaces: 
    - IUnknown
    - [IQueryInfo](https://learn.microsoft.com/en-us/windows/win32/api/shlobj_core/nn-shlobj_core-iqueryinfo):
        - GetInfoFlags: Gets the information flags for an item. **This method is not currently used.**
        - GetInfoTip: Gets the info tip text for an item.
---

# [Copy Hook Handler](https://learn.microsoft.com/en-us/windows/win32/shell/how-to-create-copy-hook-handlers) #

- Interfaces: 
    - IUnknown
    - [ICopyHook](https://learn.microsoft.com/en-us/windows/win32/shell/how-to-create-copy-hook-handlers):
        - CopyCallback: Called to approve or deny copy operation

---

# [Data Handler (file specific)](https://learn.microsoft.com/en-us/windows/win32/shell/how-to-create-data-handlers) #

- Interfaces: 
    - IUnknown
    - [IPersistFile](https://learn.microsoft.com/en-us/windows/win32/api/objidl/nn-objidl-ipersistfile)
        - GetCurFile: Retrieves the current name of the file associated with the object. If there is no current working file, this method retrieves the default save prompt for the object.
        - IsDirty: Determines whether an object has changed since it was last saved to its current file.
        - Load: Opens the specified file and initializes an object from the file contents.
        - Save: Saves a copy of the object to the specified file.
        - SaveCompleted: Notifies the object that it can write to its file.
    - [IDataObject](https://learn.microsoft.com/en-us/windows/win32/api/objidl/nn-objidl-idataobject):
        - 9 methods which I will not include here... click interface link for more details

---

# All About Hijacking #

- Installing all these handlers requires `Admin` privilges
    - Requires writes to:
        - HKEY_LOCAL_MACHINE (IconOverlay)
        - HKEY_CLASSES_ROOT (Other Handlers such as file type specific)
    - Privileged can be noisy

- COM Objects vulnerable to COM Hijacking!
    - Since all these extensions require COM, they are vulnerable to COM Hijacking
    - COM hijacking doesn't require admin privs
        - Regestry writes needed for `HKEY_CURRENT_USER\Software\Classes\CLSID\`
            - add key
            - set dll path
            - set ThreadingModel (apartment)

- More on [COM Hijacking](https://cyberstruggle.org/2021/12/14/com-hijacking-for-persistence/)

---

# More References # 

- Windows Internals for Reverse Engineers by Yarden Shafir (https://recon.cx/2023/trainingWindowsInternals.html): learned about the existence of shell extensions this way.
- https://learn.microsoft.com/en-us/windows/win32/shell/shell-entry
- https://learn.microsoft.com/en-us/windows/win32/shell/shell-exts
- https://learn.microsoft.com/en-us/windows/win32/shell/int-shell-exts // have yet to do this :) 
- https://www.codeproject.com/Articles/633/Introduction-to-COM-What-It-Is-and-How-to-Use-It
- https://www.codeproject.com/Articles/441/The-Complete-Idiot-s-Guide-to-Writing-Shell-Extens
- https://cloud.tencent.com/developer/ask/sof/107196504
- https://scorpiosoftware.net/2021/12/11/icon-handler-with-atl/
- https://github.com/zodiacon/DllIconHandler
- https://wikileaks.org/ciav7p1/cms/page_2621765.html
- https://cyberstruggle.org/2021/12/14/com-hijacking-for-persistence/