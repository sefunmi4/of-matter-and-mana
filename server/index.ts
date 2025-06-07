import express from 'express';
import bodyParser from 'body-parser';
import dotenv from 'dotenv';
import rippleEngine from './rippleEngine';

dotenv.config();

const app = express();
app.use(bodyParser.json());

app.use('/ripple', rippleEngine);

if (require.main === module) {
  const PORT = process.env.PORT || 3000;
  app.listen(Number(PORT), () => {
    console.log(`Server running on port ${PORT}`);
  });
}

export default app;
