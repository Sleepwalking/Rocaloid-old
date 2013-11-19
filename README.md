Rocaloid is a vocal synthesis system which aims at synthesizing songs with outstanding quality, flexibility and speed.

The Rocaloid Project not only contains a synthesizer, but also provides a set of tools from signal processing library to music score editor.

* Language: C(Engine), C++(Subsidiaries)
* License : GPLv3
* Platform: x86(with SSE instruction set)

Rocaloid3 is currently under construction.

Build
---

First you need qmake.

Then get [`CVEDSP`][2] and place it at ./CVEDSP.

If you want to build CVDBToolChain/SpeakerAna, though it is obsoleted, you need to get [`CVEANN`][3] and place it at ./CVEANN.

Compile CVEDSP(and CVEANN) first, then compile any .pro you want to use.

Directorys
---

* RDesign: Charts & Graphs & Specifications & Plans
* RUtil: A tiny C library for dynamic structures and file access.
* RocaloidEngine: Contains `CVE 3`, `CGTOR 3`, `RFILE 3`.
	* `CVE 3`: The vocal synthesizer (CyberVoice Engine)
		* Synthesizer: a series of modules that manipulate waves in time or freq domain.
	* `CGTOR 3`: CVS Generator, generates `CVS` from `RVS` with `CDT`.
	* `RFILE 3`: Provides I/O for `CVS`, `RVS`, `CDT` and `CVDB`.
		* `CDT3` : Cybervoice (vocal) DicTionary.
		* `CVDB3`: CyberVoice DataBase.
		* `CVS3` : Cybervoice Vocal Script.
		* `RVS3` : Rocaloid Vocal Script.
* RocaloidDevTools: tools for building Rocaloid sound dbs.
	* CVDBToolChain: a set of tools related with `.cvdb` format.
		* DBMake: this tool automatically calls other toolchain components.
		* WSplit: wave spliter.
		* Wpp   : wave preprocessor.
		* CMin  : tool for generating `.cvdb`.
		* C2Wav : `.cvdb` inspector.
		* SpeakerAna: analyze speaker characteristics, generates `.cspr` for CMin. (Obsoleted)
		* FormantMarker: spectrum visulizer used for fitting LCFECSOLA parameters. (Depends on Qt)
		* TCFILE: toolchain IO support.
	* GeneticOptimizer: an implemention of Genetic Algorithm for optimizing parameters (for certain algorithms used in Rocaloid).
	* FormantTester: visualize spectrums for testing algorithms & evaluating the quality of FECSOLA. (Obsoleted)
	* RSandBox: this is just a tester.

Depending Libraries
---

* [`CVEDSP`][2]: Signal processing lib for `CVE`.
* [`CVEANN`][3]: Artificial Neural Network lib for Rocaloid.

For more information about Rocaloid, please visit http://bbs.ivocaloid.com/forum-138-1.html (Chinese).


 [1]: https://github.com/qtau-devgroup/editor "QTau"
 [2]: https://github.com/Sleepwalking/CVEDSP "CVEDSP"
 [3]: https://github.com/Sleepwalking/CVEANN "CVEANN"
