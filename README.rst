colortemp
=========

|coverity|

.. |coverity| image:: https://img.shields.io/coverity/scan/7728.svg
   :alt:              Coverity Scan Build Status
   :target:           https://scan.coverity.com/projects/halosghost-colortemp

This is my personal fork and copy of Tedu's `sct <http://www.tedunangst.com/flak/post/sct-set-color-temperature>`_.

I cleaned up the code (a bit), pared it down to the necessary parts and may, in the future add some extra features (e.g., querying the current color temperature / a very simple daemon à la redshift).

*Note:* ``sct`` is only meant to function correctly in 500K increments (anything in between will cause incredibly weird results).
