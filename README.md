Rocaloid is a vocal synthesis engine which aims at synthesizing songs with outstanding quality, flexibility and speed.

* License: GPLv3
* Platform: x86(SSE)


---

General Structure of Rocaloid3, which is currently under construction:

![rocaloid3](https://f.cloud.github.com/assets/4531595/1055721/2b3f15a0-1144-11e3-8395-dd49d691c911.png)

We are planning to use [QTau] [1] as editor.

Directorys
---

* RDesign: Charts & Graphs & Specifications & Plans
* RUtil: A tiny C library for dynamic structures and file access.
* RocaloidEngine: Contains `CVE 3`, `CGTOR 3`, `RFILE 3`.
	* `CVE 3`: The synthesis engine (CyberVoice Engine)
		* `CVEDSP`: Signal processing lib for `CVE`.
	* `CGTOR 3`: CVS Generator, generates `CVS` from `RVS` with `CDT`.
	* `RFILE 3`: Provides I/O for `CVS`, `RVS`, `CDT` and `CVDB`.
* RocaloidDevTools: tools for building Rocaloid sound dbs.
	* CVDBToolChain: a set of tools related with `.cvdb` format.
		* CMin: tool for generating `.cvdb`.
		* C2Wav: `.cvdb` inspector.
		* SpeakerAna: analyze speaker characteristics, generates `.cspr` for CMin.
	* GeneticOptimizer: an implemention of Genetic Algorithm for optimizing parameters (for certain algorithms used in Rocaloid).
	* FormantTester: visualize spectrums for testing algorithms & evaluating the quality of FECSOLA.

For more information about Rocaloid, please visit http://bbs.ivocaloid.com/forum-138-1.html (Chinese).


 [1]: https://github.com/qtau-devgroup/editor "QTau"
