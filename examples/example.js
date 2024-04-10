const { setIoImmediate, setUvImmediate } = require('../build/Release/set-io-immediate.node');
const asyncHooks = require('async_hooks');
const fs = require('fs');

const log = (...args) => {
  fs.writeSync(1, args.join(' ') + '\n');
}

const resources = {};

const hook = asyncHooks.createHook({
  init(asyncId, type, triggerAsyncId, resource) {
    resources[asyncId] = { type, triggerAsyncId };
    log('init', asyncId, type, triggerAsyncId);
  },
  before(asyncId) {
    log('before', resources[asyncId].type, asyncId, resources[asyncId].triggerAsyncId);
  },
  after(asyncId) {
    log('after', resources[asyncId].type, asyncId, resources[asyncId].triggerAsyncId);
  },
  destroy(asyncId) {
    log('destroy', resources[asyncId].type, asyncId, resources[asyncId].triggerAsyncId);
  }
});

// console.log = log ;
// hook.enable();

process.nextTick(() => {
  console.log('nextTick')
})

Promise.resolve().then(() => {
  console.log('promise')
})

setImmediate(() => {
  console.log('immediate')
})

setIoImmediate(
  () => {
    console.log('nan worker finished')
  },
  () => {
    console.log('nan worker started')
  }
)

console.log('sync')

setTimeout(() => {
  console.log('timeout')
}, 0)

setTimeout(() => {
  console.log('timeout 2')
}, 0)

Server.listen(3000, '192.168.100.24', () => {})