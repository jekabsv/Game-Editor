// Declare WASM module type for TypeScript
declare module "../wasm/*.js" {
  export interface WasmModule {
    test: () => string;
  }

  const createModule: () => Promise<WasmModule>;
  export default createModule;
}
