
nexus:
	g++ deps/v8/out/native/libv8_snapshot.a deps/v8/out/native/libv8.dylib src/nexus.h src/nexus.cc -Ideps/v8/include -Ldeps/v8/src -o nexus

.PHONY: nexus