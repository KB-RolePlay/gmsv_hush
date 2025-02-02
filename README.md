## GMSV_hush
This is a special version of this module that removes the annoying couldn't invert rot matrix spam that occurs when a player is using vehicles such as the Jeep on an x86-64 beta server. I also disabled the CreateFragments file spam that occurs when a player tries to download a file over the size limit aswell.
To compile this you will need to use [garrysmod_common](https://github.com/danielga/garrysmod_common/).

## What changes on this fork?
A GitHub Actions workflow was added to automatically compile the module and add it as the release asset.

### Note
Don't forget to put a `require("hush")` in your Lua code to load the module.