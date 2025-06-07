const express = require('express');
const router = express.Router();

// naive in-memory ripple state
let rippleState = { time: 0, amplitude: 1 };

router.get('/state', (req, res) => {
  res.json(rippleState);
});

router.post('/step', (req, res) => {
  const dt = Number(req.body.dt || 0.1);
  rippleState.time += dt;
  rippleState.amplitude = Math.cos(rippleState.time);
  res.json(rippleState);
});

module.exports = router;
