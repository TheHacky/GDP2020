using System;
using UnityEngine;

namespace Code
{
    public class Bullet : MonoBehaviour
    {
        [SerializeField] private float _lifetime = 3.0f;

        private float _timeToKill = 0.0f;
        
        private void OnEnable()
        {
            _timeToKill = Time.time + _lifetime;
        }

        private void Update()
        {
            if (Time.time >= _timeToKill) gameObject.SetActive(false);
        }

        private void OnCollisionEnter(Collision other)
        {
            // gameObject.SetActive(false);
            _timeToKill = Time.time + 0.5f;
        }
    }
}