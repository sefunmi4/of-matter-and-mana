import request from 'supertest';
import app from '../server/index';

describe('Ripple Engine API', () => {
  beforeEach(() => {
    process.env.RIPPLE_FREQUENCY = '1';
  });

  test('GET /ripple/state returns default state', async () => {
    const res = await request(app).get('/ripple/state');
    expect(res.statusCode).toBe(200);
    expect(res.body.time).toBe(0);
    expect(res.body.amplitude).toBe(1);
  });

  test('POST /ripple/step advances time', async () => {
    const res = await request(app)
      .post('/ripple/step')
      .send({ dt: 0.5 });
    expect(res.statusCode).toBe(200);
    expect(res.body.time).toBeCloseTo(0.5);
    expect(res.body.amplitude).toBeCloseTo(Math.cos(0.5));
  });

  test('POST /ripple/step rejects invalid dt', async () => {
    const res = await request(app).post('/ripple/step').send({ dt: 'abc' });
    expect(res.statusCode).toBe(400);
  });

  test('GET /ripple/state with session header creates separate state', async () => {
    const res1 = await request(app).get('/ripple/state').set('X-Session-Id', 'A');
    const res2 = await request(app).get('/ripple/state').set('X-Session-Id', 'B');
    expect(res1.body.time).toBe(0);
    expect(res2.body.time).toBe(0);
    expect(res1.body.amplitude).toBe(1);
    expect(res2.body.amplitude).toBe(1);
    expect(res1.body).not.toHaveProperty('unexpected');
  });
});
