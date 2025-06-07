import React, { useEffect, useState } from 'react';
import { useParams } from 'react-router-dom';

export default function Chapter() {
  const { book } = useParams();
  const [content, setContent] = useState('');

  useEffect(() => {
    fetch(`/chapters/${book}`)
      .then((res) => (res.ok ? res.text() : ''))
      .then(setContent)
      .catch(() => setContent(''));
  }, [book]);

  return (
    <div>
      <h2>{book}</h2>
      <pre style={{ whiteSpace: 'pre-wrap' }}>{content}</pre>
    </div>
  );
}
