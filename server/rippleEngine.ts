import { Router, Request, Response } from 'express';

const router = Router();

type RippleState = { time: number; amplitude: number };

const states = new Map<string, RippleState>();

function getState(sessionId: string): RippleState {
  if (!states.has(sessionId)) {
    states.set(sessionId, { time: 0, amplitude: 1 });
  }
  return states.get(sessionId)!;
}

router.get('/state', (req: Request, res: Response) => {
  const session = req.header('X-Session-Id') || 'default';
  const rippleState = getState(session);
  res.json(rippleState);
});

router.post('/step', (req: Request, res: Response) => {
  const session = req.header('X-Session-Id') || 'default';
  const rippleState = getState(session);
  const dt = Number(req.body.dt ?? 0.1);
  const freq = Number(process.env.RIPPLE_FREQUENCY ?? 1);
  rippleState.time += dt;
  rippleState.amplitude = Math.cos(rippleState.time * freq);
  res.json(rippleState);
});

export default router;
