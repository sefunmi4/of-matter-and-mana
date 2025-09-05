import express from 'express';
import bodyParser from 'body-parser';
import dotenv from 'dotenv';
import rippleEngine from './rippleEngine';
import chapters from './chapters';
import { log } from './logger';

dotenv.config();

const app = express();
app.use(bodyParser.json());

app.use('/ripple', rippleEngine);
app.use('/chapters', chapters);

if (require.main === module) {
  const PORT = process.env.PORT || 3000;
  app.listen(Number(PORT), () => {
    log(`Server running on port ${PORT}`);
  });
}

export default app;
