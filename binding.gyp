{
  "targets": [
    {
      "target_name": "set-io-immediate",
      "sources": ["src/nan_worker.h", "src/uv_worker.h", "src/addon.cc"],
      "include_dirs"  : [
            "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}