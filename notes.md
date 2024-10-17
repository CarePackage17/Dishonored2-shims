# Debug stuff

1400e1140 - 140000000 = 0xE1140 = RVA of function to break on

setprod rva: 2E5FB0

FunSettingProdDevelopment: 1400e1e50 - 140000000 = E1E50

fun to find in ghidra: 0x00007ff6d9592930, base addr: 0x00007FF6D92C0000 -> rva 2D2930

Very weird thing: starting via ghidra debugger goes straight into dev mode? wtf?
it still crashes, now with `FATAL ERROR: Could not find default.cfg. Check paths fs_basepath = '' fs_savepath = 'C:\Users\me\SAVEDG~1\Arkane Studios\Dishonored2'` and it's sort of right, the saved games path only has default_dev, not default.cfg. Let's copypaste it there and try again.
Also, why does this not happen in the VS debugger? Make it make sense :(

Alright, copypasting cfgs didn't help, we still crash like in the vs debugger after patching memory.
Steam is also disabled, maybe we should start that? Theoretically we don't need it in the unpacked exe, but maybe devtools do? Also, let's try windbg launch.

Yeah, starting via windbg triggers prod_development instantly. wtf. Also, resource paths look fucked. it's not loading from the game dir but instead tries from windir? wtf? let's give it fs_basepath on the command line.

Ok, so dev mode triggering has to do with missing fs_basepath? Why tf is it missing when launching from windbg? if we give it the cooked assets path it starts in production mode. Maybe it's because we don't give it a working dir in windbg?

Maybe it's looking for dev stuff in master.index (saw that in the debugger) and if it doesn't find that it assumes prod?

If we could maybe unpack all the stuff from resource files it'd work?

Alright, so starting without specifying a working directory where the game finds master.index seems to trigger PROD_DEVELOPMENT at start. The thing is, we need the files because otherwise shit doesn't start.
Maybe we'll find something interesting looking for master index in the code?

Having a master.index file in fs_basepath leads to PROD_PRODUCTION, confirmed.
Now what can we do without master.index? The game needs a bunch of files to load, otherwise we crash.

Maybe https://github.com/chipolux/disrev would help us unpack? Maybe the game itself can unpack shit again with some cmds? What about resource_outpath cvar? Who uses that?

`+resource_debugLevel 2 +fs_debug 2 +ark_fs_verbosityOnLoad 1 +resource_showLoads 1` prints some useful info.
`+fs_verbose GameFolder UserFolder` also works.

Alright, somebody made an unpacker script for quickbms. Let's see if that works (hopefully I got enough disk space smh)

So, I guess the problem now is that the source files don't exist (although their names are mentioned in the index?!) and if we start in dev mode the game tries to load them directly. Well, fuck. Either that or the extractor tool is lying...
OR, we might be able to use voidResoureCache? Like put all the compiled files there (like the game does when we give it a fake loading screen)...but for that we need to figure out all filenames and hashes and shit.


`+s_noSound 1` to disable sound at startup. That at least gets us past that wwise crash, but now it can't find decls. Maybe we could really look into that resourceCache so the game loads all teh compiled assets instead of trying to use source files...

What if we started in the compiled folder but gave it a different fs_cachepath?

Going back to the wtf of why are we running in PROD_DEVELOPMENT under the ghidra debugger: https://github.com/NationalSecurityAgency/ghidra/issues/4732

SomeStartupFunction RVA: 1401e8050-140000000 = 1E8050
1401e8177-140000000 = 1E8177

check idstudio launch global rva: 140204b44-140000000 = 204B44
in debugger atm 

debug the FunInCaseOfIdStudioDevCmdLine some more, maybe it has something interesting still.

140204c14-140000000 = 204C14


---------------------------------------------------------------

Running with +idstudio +editmap on the command line attempts to start the editor...but it still crashes because we're in production mode :/

crashing fun with iggyerfmon: 00007FF65AB73D50-00007FF658700000 = 2473D50

legit iggyerfmon allocs: 65536, 16, 32768, 2672 (similar callstack to crash loc), 8, 2672, 16, free call, then havok crash

first alloc happens in iggyperfmoncreate, 65536 bytes, addr 0000027F4FCEE040
- 16 bytes, addr 0000027F76620760
- 32768 bytes, addr 0000027F4FE85060
iggyperfmoncreate returns 0000027F4FCEE040

the the game calls some (internal?) function in iggyperfmon and more allocs happen. I think this is our crash site looking at the log state. Now what does that function do and how does it even get the address, wtf?
unless...what init returns is a struct and not just some random shit it got from malloc.

memory at return value from legit dll:
0x0000028F54708D30  f0 27 76 a4 f9 7f 00 00 30 27 76 a4 f9 7f 00 00  ð'v¤ù...0'v¤ù...
0x0000028F54708D40  70 52 76 a4 f9 7f 00 00 10 27 76 a4 f9 7f 00 00  pRv¤ù....'v¤ù...
0x0000028F54708D50  f0 81 76 a4 f9 7f 00 00 90 80 76 a4 f9 7f 00 00  ð.v¤ù....€v¤ù...
0x0000028F54708D60  00 28 76 a4 f9 7f 00 00 68 f4 00 00 00 00 00 00  .(v¤ù...hô......
0x0000028F54708D70  ff ff ff ff ff ff ff ff ff ff ff ff 00 00 00 00  ÿÿÿÿÿÿÿÿÿÿÿÿ....

there's probably function pointers in here called whenever. yay, more abi to figure out ._.
Also, one of these might be the address of a malloc'd block?
For sure the call that crashes on our side (with random shit addresses) is supposed to go into iggyperfmon, so that confirms the function pointer hypothesis. Also, the addr in that run is 00007FF9A47681F0, which is in the 3rd row of that hex dump above. well. in ghidra it's FunThatCrashesWithShimIggyPerfmon.

Cool, some sort of progress at least. I wish there was at least a fucking public header or something to make this less of a guesswork. oh well.

# Frida

## Faking date/time for havok

This eliminates the need to set the system clock before starting (annoying af because it breaks any internet access).
`frida-trace -a "Dishonored2_x64_steamless.exe!0x288aff0" .\Dishonored2_x64_steamless.exe +com_showLoadingScreen 0 +win_viewLog 1`

sub_288aff0.js:
```js
{
  /**
   * Called synchronously when about to call sub_288aff0.
   *
   * @this {object} - Object allowing you to store state for use in onLeave.
   * @param {function} log - Call this function with a string to be presented to the user.
   * @param {array} args - Function arguments represented as an array of NativePointer objects.
   * For example use args[0].readUtf8String() if the first argument is a pointer to a C string encoded as UTF-8.
   * It is also possible to modify arguments by assigning a NativePointer object to an element of this array.
   * @param {object} state - Object allowing you to keep state across function calls.
   * Only one JavaScript function will execute at a time, so do not worry about race-conditions.
   * However, do not use this to store function arguments across onEnter/onLeave, but instead
   * use "this" which is an object for keeping state local to an invocation.
   */
  onEnter(log, args, state) {
    log("havok's BS checks");
  },

  /**
   * Called synchronously when about to return from sub_288aff0.
   *
   * See onEnter for details.
   *
   * @this {object} - Object allowing you to access state stored in onEnter.
   * @param {function} log - Call this function with a string to be presented to the user.
   * @param {NativePointer} retval - Return value represented as a NativePointer object.
   * @param {object} state - Object allowing you to keep state across function calls.
   */
  onLeave(log, retval, state) {
	  //Let's pretend it's 17.10.2018
	  retval.replace(1539792002);
  }
}
```