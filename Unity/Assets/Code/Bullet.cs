using System;
using UnityEngine;

namespace Code
{
    public class Bullet : MonoBehaviour
    {
        [SerializeField] private float _lifetime = 3.0f;
        [SerializeField] private ParticleSystem _explosionPrefab = null;
        [SerializeField] private AudioClip _explosionSound = null;
        
        private AudioSource _audioSource = null;

        private float _timeToKill = 0.0f;

        private void Start()
        {
            _audioSource = FindObjectOfType<AudioSource>();
        }

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
            // _timeToKill = Time.time + 0.5f;
            _timeToKill = Time.time;

            _audioSource.PlayOneShot(_explosionSound);
            ContactPoint point = other.GetContact(0);
            Instantiate(_explosionPrefab, point.point, Quaternion.LookRotation(point.normal));
        }
    }
}