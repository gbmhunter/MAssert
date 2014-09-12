=======
MAssert
=======

------------------------------------------------------------------
A microcontroller-friendly C++ assert() for embedded applications.
------------------------------------------------------------------

.. image:: https://api.travis-ci.org/mbedded-ninja/MAssert.png?branch=master   
	:target: https://travis-ci.org/mbedded-ninja/MAssert

- Author: gbmhunter <gbmhunter@gmail.com> (http://www.mbedded.ninja)
- First Ever Commit: 2014-09-01
- Last Modified: 2014-09-12
- Version: v1.2.0.0
- Company: mbedded.ninja
- Project: MToolkit
- Language: C++
- Compiler: GCC	
- uC Model: n/a
- Computer Architecture: n/a
- Operating System: n/a
- Documentation Format: Doxygen
- License: GPLv3

Description
===========

MAssert is a microcontroller-friendly C++ assert() for embedded applications.

Features:

- Embedded (microcontroller) support
- Small flash/RAM memory footprint (no depedance on the C++ std::string class)
- Unit tests
- Doxygen-style well-documented API.
- Portability

External Dependencies
=====================

Nothing here yet.

Issues
======

See GitHub Issues.

Limitations
===========

Nothing here yet.

Usage
=====

See the unit tests in the 'test/' directory for basic examples.
	
Changelog
=========

========= ========== ===================================================================================================
Version   Date       Comment
========= ========== ===================================================================================================
v1.2.0.0  2014-09-12 Updated Makefile to download and build dependencies correctly. Switched from using UnitTestCpp to MUnitTest, closes #3.
v1.1.0.0  2014-09-12 Updated name in README and Eclipse project files from MAssertCpp to just MAssert.
v1.0.1.0  2014-09-02 Added 'MbeddedNinja' namespace qualifier to assert macros.
v1.0.0.0  2014-09-01 Initial commit. Basic assert() functions working and unit tests running on build.
========= ========== ===================================================================================================