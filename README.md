Server Killer
--------

I developed this back in 2008 to expose a kill switch built into Knight Online server files along with the associated patch. It now only serves for educational, and historical purposes.

## Patch

Though I don't have the full analysis anymore, the patch was pretty straightforward and just required nopping (0x90) that particular part of the switch:

* 00490E95 50 PUSH EAX
* 00490E96 E8 9C29F7FF CALL 00403837
